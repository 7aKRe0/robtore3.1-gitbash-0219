#include "some.h"


#define REDUCTION_RATIO 0.4 // 減速比
#define DISTANCE_PER_CNT (M_PI * TIRE * REDUCTION_RATIO / ENCODER_CPR) //[mm per cnt]


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


int cross_flag = 0;



uint32_t start_time = 0;

int32_t cnt_new_L;
int32_t cnt_new_R;
int32_t cnt_L;
int32_t cnt_R;

int32_t accumulation;


float Kp = 0.1;
float Kd = 0.003;
float base_speed1;
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
       while(1){//SW1

    	   if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) == GPIO_PIN_RESET){
    		   break;
    	   }
           //readSens();
           LED_RGB_2(2);

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
//	for(int k = 1; k < 6;k++){
//		Line1_sum +=Line_sum[k];
//		Line2_sum +=Line_sum[k+6];
//
//	}
		Line1_sum =Line_sum[1]+Line_sum[2]+Line_sum[3]+Line_sum[4]+Line_sum[5];
		Line2_sum =Line_sum[7]+Line_sum[8]+Line_sum[9]+Line_sum[10]+Line_sum[11];


		uint16_t  average_cross = Line_sum[2] + Line_sum[10];
		if(average_cross <600){
			 cross_flag = 1;
			 start_time = HAL_GetTick();
		}

		if(cross_flag == 1){
			LED_RGB(4);
			if((HAL_GetTick() - start_time) < 400){
				LED_RGB(2);
			}else{
			cross_flag = 0;
			LED_RGB(1);
			}

		}else{
			readSens2();
		}


	return  Line1_sum - Line2_sum;
}


// int32_t cnt_test; //Max value is 2048

float calculateEncoderSpeed(){

//	cnt_new_L =  TIM4 -> CNT - OFFSET; //dL
//	cnt_new_R =OFFSET- TIM3 -> CNT; //dR
	cnt_new_L =  TIM4 -> CNT ; //dL
	cnt_new_R = TIM3 -> CNT; //dR

	 TIM4 -> CNT=32767;
	 TIM3 -> CNT=32767;

//	cnt_test = TIM3 -> CNT;
	cnt_L = -(cnt_new_L - 32767);
	cnt_R = -(cnt_new_R - 32767);

//	cnt_L = cnt_new_L ;
//	cnt_R = cnt_new_R;



	distance_1ms = DISTANCE_PER_CNT * (cnt_L + cnt_R) / 2;
//	accumulation += distance_1ms;
	distance_1ms_L = DISTANCE_PER_CNT * cnt_L;
	distance_1ms_R = DISTANCE_PER_CNT * cnt_R;



//	if(cnt_new_L != cnt_old_L || cnt_new_R != cnt_old_R){
//		char scnt[100];
////		sprintf(scnt, "Speed: %f\r\n", distance_1ms);
//
//	}
	cnt_old_L = cnt_new_L;
    cnt_old_R = cnt_new_R;

//    TIM4 -> CNT = OFFSET;
//    TIM3 -> CNT = OFFSET;
    return distance_1ms;
}




float EncoderSpeed() {


	float  target_speed = 0;
	float Sp = 800;
	float Si = 8000;
	//speed_error
	//target_speedを個別に決める
	target_speed =0.03;
	float adjusted_speed = target_speed - calculateEncoderSpeed();

	static float integral= 0;
	integral += adjusted_speed * dt;


//    static float previous_adjusted_speed_L = 0, previous_adjusted_speed_R = 0;


	//P
	float speed_P_gain = Sp * adjusted_speed;
	//I
    float speed_I_gain = Si * integral;



	#define I_LIMIT 1000
	if (integral > I_LIMIT) integral= I_LIMIT;
	if (integral < -I_LIMIT) integral = -I_LIMIT;


	float duty = speed_P_gain + speed_I_gain;

    if (duty > 300) duty = 300;
    if (duty < -300) duty = -300;


    previous_speed_error = adjusted_speed;


	float motor = duty;
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

//	     float duty_L = 80 - output;
//	     float duty_R = 80 + output;
//		     float duty_L =- output+base_speed1;
//		     float duty_R = output+base_speed1;

//	     float duty_L =base_speed1;
//	     float duty_R = base_speed1;

	     float sp =EncoderSpeed();

	     float motor_L = output + sp;
	     float motor_R = -output + sp;



	     if (motor_L > 350) motor_L = 350;
	     if (motor_L < -350) motor_L = -350;
	     if (motor_R > 350) motor_R = 350;
	     if (motor_R < -350) motor_R = -350;


	     // モータ
	     ControlMotor(motor_L, motor_R);
}




