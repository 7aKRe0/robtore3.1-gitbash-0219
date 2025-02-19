#include "some.h"


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

int cross_flag = 0;

uint32_t start_time = 0;


float Kp = 0.2;
float Kd = 0.05;
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



//void calibrate_sensors(void){
//       for (int i = 0; i < 50000; i++) {
//           readSens();
//           readSens2();
//
//
//           for(int k = 0; k < SENSOR_COUNT; k++){
//        	   if(Line1_sens[k] < min_black_a[k]){
//        		   min_black_a[k] = Line1_sens[k];
//        	   }
//        	   if(Line1_sens[k] > max_white_a[k] ){
//        		   max_white_a[k] = Line1_sens[k];
//        	   }
//
//        	   if(Line2_sens[k] < min_black_b[k]){
//        		   min_black_b[k] = Line2_sens[k];
//        	   }
//        	   if(Line2_sens[k] > max_white_b[k] ){
//        		   max_white_b[k] = Line2_sens[k];
//        	   }
//        	   }
//
//
//       }
//
//   }

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
		     float duty_L =- output+base_speed1;
		     float duty_R = output+base_speed1;

	     float motor_L = -1*(duty_L);
	     float motor_R = -1*(duty_R);



	     if (motor_L > 350) motor_L = 200;
	     if (motor_L < -350) motor_L = -200;
	     if (motor_R > 350) motor_R = 200;
	     if (motor_R < -350) motor_R = -200;

	     // モータ
	     ControlMotor(motor_L, motor_R);
}




