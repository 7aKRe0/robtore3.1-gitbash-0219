#include "some.h"

//SW2 PB15 SW1 PC13

int mode =0;
int calibrate_count =0;
//int mode_processed;

void ButtonPress(void){
	mode=0;
	LED_RGB_2(6);
	HAL_Delay(1000);

	while(1){
    if (HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) == GPIO_PIN_RESET)//SW1
    {
    	HAL_Delay(1000);
    	break;

    }

    if (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15) == GPIO_PIN_RESET)//SW2
    {
    	mode++;
    	LED_RGB(mode);
		HAL_Delay(200);

        if(mode >7){
        	mode = 0;
        }
//        mode_processed = 0;
     //   LED_RGB(0);
    }
	}

}



void mode_test(void){


  switch(mode)
	  {
	  case 1:
		  LED_RGB(mode);
		  if(calibrate_count == 0){
			  calibrate_sensors();
			  calibrate_count = 1;
		  }
//		  LED_RGB(0);
//		  base_speed1=0;




		  break;

	  case 2:
		  LED_RGB(mode);

		  LED_RGB_2(3);
		  LED_RGB(3);
		  target_speed =0.0;

	//	while(1);
		  HAL_TIM_Base_Start_IT(&htim6);
		  test_DD();
//		HAL_TIM_Base_Stop_IT(&htim6);
		ControlMotor(0, 0);
		  LED_RGB(0);
//		  base_speed1=0;
		  break;


	  case 3:
		  LED_RGB(mode);
//		  HAL_TIM_Base_Start_IT(&htim6);
		  LED_RGB(0);


		  target_speed =1.8;
//		  1.8 kansou
		  HAL_TIM_Base_Start_IT(&htim6);
		  HAL_TIM_Base_Start_IT(&htim7);//test

		  test_DD();
//		  base_speed1=-125;


		  break;

	  case 4:
		  LED_RGB(mode);
//		  HAL_TIM_Base_Start_IT(&htim6);
		  LED_RGB(0);

		  target_speed =2.0;
		  HAL_TIM_Base_Start_IT(&htim6);
		  HAL_TIM_Base_Start_IT(&htim7);//test


		  test_DD();

//		  base_speed1=-127;
		  break;


	  case 5:
		  LED_RGB(mode);
//		  HAL_TIM_Base_Start_IT(&htim6);
		  LED_RGB(0);

		  target_speed =2.2;
		  HAL_TIM_Base_Start_IT(&htim6);
		  HAL_TIM_Base_Start_IT(&htim7);//test


		  test_DD();

//		  base_speed1=-129;

		  break;

	  case 6:
		  LED_RGB(mode);
//		  HAL_TIM_Base_Start_IT(&htim6);
		  LED_RGB(0);

		  target_speed =2.3;
		  HAL_TIM_Base_Start_IT(&htim6);
		  HAL_TIM_Base_Start_IT(&htim7);//test


		  test_DD();

//		  base_speed1=-129;

		  break;

	  case 7:
		  LED_RGB(mode);
//		  HAL_TIM_Base_Start_IT(&htim6);
		  LED_RGB(0);

		  target_speed =0.0;

		  PrintVelocityData();

//		  HAL_TIM_Base_Start_IT(&htim6);
		  test_DD();

//		  base_speed1=-129;

		  break;

	  default:
		  LED_RGB(7);
//		  base_speed1=0;
//		  target_speed =0.0;



		  break;

	  }
}

void change_mode(){
	ButtonPress();
	mode_test();
//		calculateEncoderSpeed();

}

void test_DD(){
	test_flag =0;
	TIM4 -> CNT=32767;
	TIM3 -> CNT=32767;
	LED_RGB_2(3);
	while (1) {
//		readSens2();
//		test_flag = 1;

		//change_mode();

		if (Line3_sens[1] == 0 && cross_flag ==0) {
			while (1) {

				if (Line3_sens[1] == 1) {
					test_flag++;
					break;
				}
			}
		}

		if (test_flag >= 2) {
				LED_RGB_2(7);
				HAL_TIM_Base_Stop_IT(&htim6);
				HAL_TIM_Base_Stop_IT(&htim7);//test

				ControlMotor(0, 0);
			break;


		}

	}

	calculateEncoderSpeed();
	HAL_TIM_Base_Start_IT(&htim6);


	 accumulation = 0;
	 target_speed = 1.1;
     calculateEncoderSpeed();
 	LED_RGB_2(5);



	    while (accumulation < 45) {
	        accumulation += distance_1ms;
//	        ControlMotor(110, 110);
	        HAL_Delay(10);
	    }


	LED_RGB_2(2);
	HAL_TIM_Base_Stop_IT(&htim6);
	ControlMotor(0, 0);
	return 0;
}
