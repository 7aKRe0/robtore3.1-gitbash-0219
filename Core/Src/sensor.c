#include "some.h"
#include "segment.h"

#define REDUCTION_RATIO 0.4 // 減速比
#define DISTANCE_PER_CNT (M_PI * TIRE * REDUCTION_RATIO / ENCODER_CPR) //[mm per cnt]

//#define MAX_RECORDS 500000

float  accumulation;
float Kp = 0.1;
float Kd = 0.002;
float base_speed1;


float distance_1ms,distance_1ms_L,distance_1ms_R;

static int32_t cnt_old_L = 0, cnt_old_R = 0;


float Line1_sens[SENSOR_COUNT];  // 実体の定義
float Line2_sens[SENSOR_COUNT];
float Line3_sens[2];  // readSens2() で使用

uint16_t Line_sens[13];
float  Line_min[SENSOR_COUNT] = {3000, 3000, 3000, 3000, 3000, 3000,3000, 3000, 3000, 3000, 3000, 3000,3000};
float Line_max[SENSOR_COUNT] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
float Line_sum[SENSOR_COUNT];
float Line1_sum = 0;
float Line2_sum = 0;
float previous_error, integral;
float previous_speed_error;
float  target_speed = 0;
int cross_flag = 0;


uint32_t start_time = 0;
int32_t cnt_new_L;
int32_t cnt_new_R;
int32_t cnt_L;
int32_t cnt_R;
int32_t test_cnt_L;
int32_t test_cnt_R;

//static uint16_t index = 0;





int32_t VP_L[MAX_RECORDS] = {0};
int32_t VP_R[MAX_RECORDS] = {0};
uint8_t VP_S[MAX_RECORDS] = {0};



/* ---- 実体定義 ----------------------------------------------- */
volatile RunMode  runMode      = MODE_RECORD;
SegmentInfo       segTbl[MAX_SEG-1];
uint8_t           segCnt       = 0;

uint16_t  marker_idx[MAX_SEG];
uint8_t   marker_cnt = 0;

uint16_t  record_index = 0;
volatile uint8_t marker_flag = 0;


void MX_ADC1_Init(void);
void readSens(void){


    for (uint8_t i = 0; i < 6; i++) {
        Line1_sens[i] = Line_sens[i];//L
        Line2_sens[i] = Line_sens[i+7];//R

    }
}


void readSens2(){
	Line3_sens[0] = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2);//L
    Line3_sens[1] = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_15);//R

}


void calibrate_sensors(void){    

    for (int k = 0; k < SENSOR_COUNT; k++) {
        Line_min[k] = 3000.0;  // 初期値
        Line_max[k] = 0.0;     // 初期値
    }
HAL_Delay(500);
       while(1){//SW2

    	   if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15) == GPIO_PIN_RESET){
    		   break;
    	   }
           //readSens();
           LED_RGB_2(2);
           LED_RGB(2);
           for(int k = 0; k < SENSOR_COUNT; k++){
        	   if(Line_sens[k] < Line_min[k]){
        		   Line_min[k] = Line_sens[k];
        	   }
        	   if(Line_sens[k] > Line_max[k] ){
        		   Line_max[k] = Line_sens[k];
			   }
		   }
	   }

       LED_RGB_2(0);

	}


float sens_get(void){
	float Line1_sum = 0.0;
	float Line2_sum = 0.0;
//	static const int g1[SENSOR_COUNT] = {1,1,1,1,1,1,1,1,1,1,1,1,1};//L
//	static const int g2[] = {1,1,1,1,1,1};


	for (int i = 0; i < SENSOR_COUNT; i++){
		float range = Line_max[i] - Line_min[i];
			if(range == 0){
				range = 1;
			}
			if(Line_min[i] >=Line_sens[i]){
				Line_sens[i] = Line_min[i];
			}
		Line_sum[i] =0.0;
		//Line_sum[i] = (Line_sens[i]/ Line_max[i])*1000;
		Line_sum[i]=((Line_sens[i]-Line_min[i] )/range)*1000;
		if(Line_sum[i]>1000)Line_sum[i]=1000;

	}

		Line1_sum =Line_sum[1]+Line_sum[2]+Line_sum[3]+Line_sum[4]+Line_sum[5];
		Line2_sum =Line_sum[7]+Line_sum[8]+Line_sum[9]+Line_sum[10]+Line_sum[11];


		average_cross = (Line_sum[2] + Line_sum[10])/2;

//		}
//

	return  Line1_sum - Line2_sum;
}


// int32_t cnt_test; //Max value is 2048

float calculateEncoderSpeed(){
	 static bool first_call = true;

	cnt_new_L =  TIM4 -> CNT ; //dL
	cnt_new_R = TIM3 -> CNT; //dR


	 if (first_call) {

	        TIM4->CNT = 32767;
	        TIM3->CNT = 32767;

	        // 次回のために old も 32767 に同期
	        cnt_old_L = 32767;
	        cnt_old_R = 32767;
//	    	cnt_old_L = cnt_new_L;
//	        cnt_old_R = cnt_new_R;

	        first_call = false;
	        // 初回は計算せず return 0
	        return 0.0f;
	    }


	 TIM4 -> CNT=32767;
	 TIM3 -> CNT=32767;


//	 test_cnt_L =TIM4 -> CNT ;
//	 test_cnt_R =TIM3 -> CNT;

	cnt_L = -(cnt_new_L - 32767);
	cnt_R = -(cnt_new_R - 32767);





	distance_1ms = DISTANCE_PER_CNT * (cnt_L + cnt_R) / 2;
//	accumulation += distance_1ms;
	distance_1ms_L = DISTANCE_PER_CNT * cnt_L;
	distance_1ms_R = DISTANCE_PER_CNT * cnt_R;



	if(average_cross <250){
		 cross_flag = 1;
		 accumulation = 0;
		 LED_RGB(1);
	}

	if(cross_flag == 1){
//		 LED_RGB(1);
		accumulation +=distance_1ms;
		if(accumulation >800){
			cross_flag = 0;
			accumulation = 0;
			LED_RGB(0);
		}
	}else{
	}



	cnt_old_L = cnt_new_L;
    cnt_old_R = cnt_new_R;


    return distance_1ms;
}




float EncoderSpeed() {


	float Sp = 800;
	float Si = 8000;

	float adjusted_speed = target_speed - calculateEncoderSpeed();

	static float integral= 0;
	integral += adjusted_speed * dt;



	//P
	float speed_P_gain = Sp * adjusted_speed;
	//I
    float speed_I_gain = Si * integral;



	#define I_LIMIT 1000
	if (integral > I_LIMIT) integral= I_LIMIT;
	if (integral < -I_LIMIT) integral = -I_LIMIT;


	float duty = speed_P_gain + speed_I_gain;

    if (duty > 250) duty = 250;
    if (duty < -250) duty = -250;


    previous_speed_error = adjusted_speed;




    // モータ
    return duty;
}



void SpeedControl_NoENC() {

//		readSens2();

	     float error = sens_get();
	     // PD
	     float derivative = (error - previous_error) / dt;

	     float P =Kp * error;
	     float D =Kd * derivative;

	     float output = P + D;
	     previous_error = error;

	     float sp =EncoderSpeed();

	     float motor_L = output + sp;
	     float motor_R = -output + sp;


	     float max_output = 499;


	     float overflow_L = 0;
	     float overflow_R = 0;

	     if (motor_L > max_output) {
	         overflow_L = motor_L - max_output;
	         motor_L = max_output;
	     } else if (motor_L < -max_output) {
	         overflow_L = motor_L - max_output;
	         motor_L = -max_output;
	     }

	     if (motor_R > max_output) {
	         overflow_R = motor_R - max_output;
	         motor_R = max_output;
	     } else if (motor_R < -max_output) {
	         overflow_R = motor_R - max_output;
	         motor_R = -max_output;
	     }



	     if (overflow_L > 0) {
	         motor_R -= overflow_L;
	     }
	     if (overflow_L < 0) {
	         motor_R += overflow_L;
	     }
	     if (overflow_R > 0) {
	         motor_L -= overflow_R;
	     }
	     if (overflow_R < 0) {
	         motor_L += overflow_R;
	     }


	     // モータ
	     ControlMotor(motor_L, motor_R);
}


//uint16_t record_index = 0;
//volatile uint8_t marker_flag = 0;

//追加4.18
uint16_t marker_idx[MAX_SEG];   // マーカー位置
//uint8_t  marker_cnt = 0;

float posX[MAX_RECORDS+1];
float posY[MAX_RECORDS+1];

uint8_t curSeg = 0;


void BuildSegmentTable(void)
{
    segCnt = marker_cnt - 1;
    for(uint8_t s = 0; s < segCnt; s++){
        uint16_t a = marker_idx[s];
        uint16_t b = marker_idx[s+1];
        uint16_t n = b - a + 1;
        // --- 点群を tmp バッファにコピー ---
        Position pts[256];                // n が小さい想定
        for(uint16_t i=0;i<n;i++){
            pts[i].x = posX[a+i];
            pts[i].y = posY[a+i];
        }
        float cx,cy,R;
        fit_circle_kasa(pts, n, &cx,&cy,&R);
        segTbl[s].R     = R;
        segTbl[s].speed = decideSpeed(R);
    }
}



void VelocityPlan(void)
{
    if(record_index >= MAX_RECORDS) return;

    // ──1) エンコーダ生保存──
    VP_L[record_index] = cnt_L;
    VP_R[record_index] = cnt_R;

    // ──2) マーカーフラグ保存──
    VP_S[record_index] = marker_flag;
    if(marker_flag){
        marker_idx[marker_cnt++] = record_index;
        marker_flag = 0;
    }

    // ──3) オドメトリ更新──
    if(record_index>0){
        odom_update(record_index);        // Δx,Δy 積分→posX/Y
    }

    record_index++;
}


float decideSpeed(float R)
{
    if(R <= 0.05f) return 0.8f;    // 直線 → 高速
    if(R <= 0.08f) return 1.0f;    // 中カーブ → 中速
    return 1.5f;                   // 急カーブ → 低速.直線？
}



void PrintVelocityData() {
    printf("=== Velocity Data ===\r\n");
//    for (uint16_t i = 0; i < MAX_RECORDS; i++) {
//
////        printf("%ld, %ld\r\n", VP_L[i], VP_R[i]);
//    	printf("%ld, %ld, %d\r\n", VP_L[i], VP_R[i], VP_S[i]);
//
//
//    }
    for(uint8_t i = 0; i < segCnt; i++){
        printf("Seg[%d]: R = %.2f, Speed = %.2f\r\n", i, segTbl[i].R, segTbl[i].speed);
    }

}

void odom_update(uint16_t idx)
{
    if(idx==0) return;
    /* 1回目とそれ以降のカウント差をミリメートルへ変換 */
    float dL = (VP_L[idx] - VP_L[idx-1]) * ENC_MM_PER_CNT;
    float dR = (VP_R[idx] - VP_R[idx-1]) * ENC_MM_PER_CNT;

    float dS = (dL + dR) * 0.5f;
    static float theta = 0.0f;
    theta += (dR - dL) / TREAD_MM;

    posX[idx] = posX[idx-1] + dS * cosf(theta);
    posY[idx] = posY[idx-1] + dS * sinf(theta);
}

void fit_circle_kasa(Position* pts, uint16_t n,
                     float* cx, float* cy, float* R)
{
    if(n < 3){                 /* 点が少な過ぎる → 退化 */
        *cx = *cy = 0.0f;  *R = INFINITY;
        return;
    }

    /* ---------- １パスで必要な総和を計算 ---------- */
    double Sx=0, Sy=0, Sx2=0, Sy2=0, Sx3=0, Sy3=0, Sxy=0, Sx2y=0, Sxy2=0;

    for(uint16_t i=0; i<n; i++){
        double x = pts[i].x;
        double y = pts[i].y;
        double x2 = x*x;
        double y2 = y*y;

        Sx   += x;
        Sy   += y;
        Sx2  += x2;
        Sy2  += y2;
        Sx3  += x2*x;
        Sy3  += y2*y;
        Sxy  += x*y;
        Sx2y += x2*y;
        Sxy2 += x*y2;
    }

    /* ---------- Kasa 法の連立一次式 ---------- */
    double C = n * Sx2 - Sx*Sx;
    double D = n * Sxy - Sx*Sy;
    double E = n * Sx3 + n * Sxy2 - (Sx2 + Sy2)*Sx;
    double G = n * Sy2 - Sy*Sy;
    double H = n * Sx2y + n * Sy3 - (Sx2 + Sy2)*Sy;

    double denom = 2.0*(C*G - D*D);
    if(fabs(denom) < 1e-12){   /* ほぼ直線 → 半径∞ */
        *cx = *cy = 0.0f;  *R = INFINITY;
        return;
    }

    /* ---------- 中心座標 (a,b) ---------- */
    double a = (G*E - D*H) / denom;
    double b = (C*H - D*E) / denom;
    *cx = (float)a;
    *cy = (float)b;

    /* ---------- 半径を点群から算出（平均距離） ---------- */
    double rSum = 0.0;
    for(uint16_t i=0; i<n; i++){
        double dx = pts[i].x - a;
        double dy = pts[i].y - b;
        rSum += sqrt(dx*dx + dy*dy);
    }
    *R = (float)(rSum / n);
}
