#include "some.h"


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


uint16_t record_index = 0;
volatile uint8_t marker_flag = 0;

void VelocityPlan(){

	if (record_index < MAX_RECORDS) {
	        VP_L[record_index] = cnt_L;
	        VP_R[record_index] = cnt_R;

	        VP_S[record_index] = marker_flag;
	        record_index++;
	        marker_flag = 0;
	    }
	}

void PrintVelocityData() {
    printf("=== Velocity Data ===\r\n");
    for (uint16_t i = 0; i < MAX_RECORDS; i++) {

//        printf("%ld, %ld\r\n", VP_L[i], VP_R[i]);
    	printf("%ld, %ld, %d\r\n", VP_L[i], VP_R[i], VP_S[i]);


    }
}

