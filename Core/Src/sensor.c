#include "some.h"



void MX_ADC1_Init(void);

void readSens(void){
    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *) Line_sens,13) != HAL_OK){
                Error_Handler();
        }

    for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
        Line1_sens[i] = Line_sens[i+1];//L
        Line2_sens[i] = Line_sens[i+8];//R
    }

   }


void readSens2(){
	Line3_sens[0] = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2);//L
    Line3_sens[1] = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_15);//R

}



void calibrate_sensors(void){    
       for (int i = 0; i < 50000; i++) {
           readSens();
           readSens2();


           for(int k = 0; k < SENSOR_COUNT; k++){
        	   if(Line1_sens[k] < min_black_a[k]){
        		   min_black_a[k] = Line1_sens[k];
        	   }
        	   if(Line1_sens[k] > max_white_a[k] ){
        		   max_white_a[k] = Line1_sens[k];
        	   }

        	   if(Line2_sens[k] < min_black_b[k]){
        		   min_black_b[k] = Line2_sens[k];
        	   }
        	   if(Line2_sens[k] > max_white_b[k] ){
        		   max_white_b[k] = Line2_sens[k];
        	   }
        	   }

 
       }

   }



// void SpeedControl() {
//     float error = calculateError();
//     // PD
//     float derivative = (error - previous_error) / dt;

//     float P =Kp * error;
//     float D =Kd * derivative;

//     float output = P + D;
//     previous_error = error;

//     target_speed_L = base_speed - output;
//     target_speed_R = base_speed + output;


//     float duty_L = -1*(target_speed_L);
//     float duty_R = -1*(target_speed_R);



//     if (duty_L > 4000) duty_L = 4000;
//     if (duty_L < -4000) duty_L = -4000;
//     if (duty_R > 4000) duty_R = 4000;
//     if (duty_R < -4000) duty_R = -4000;

//     // モータ
//     controlMotor(duty_L, duty_R);
// }
