#include "some.h"

//SW2 PB15 SW1 PC13

int mode =0;
int calibrate_count =0;
//int mode_processed;

void ButtonPress(void){
    if (HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) == GPIO_PIN_RESET)//SW1
    {
//    	LED_RGB(6);
//		HAL_Delay(200);
//        mode++;
////        mode_processed = 0;
//        LED_RGB(0);
    }

    if (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15) == GPIO_PIN_RESET)//SW2
    {
    	LED_RGB(6);
		HAL_Delay(200);
        mode++;
//        mode_processed = 0;
        LED_RGB(0);
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
		  base_speed1=0;



		  break;

	  case 2:
		  LED_RGB(mode);
		  HAL_TIM_Base_Start_IT(&htim6);
		  LED_RGB(0);
		  base_speed1=0;




		  break;


	  case 3:
		  LED_RGB(mode);
//		  HAL_TIM_Base_Start_IT(&htim6);
		  LED_RGB(0);



		  base_speed1=-125;


		  break;

	  case 4:
		  LED_RGB(mode);
//		  HAL_TIM_Base_Start_IT(&htim6);
		  LED_RGB(0);



		  base_speed1=-127;
		  break;


	  case 5:
		  LED_RGB(mode);
//		  HAL_TIM_Base_Start_IT(&htim6);
		  LED_RGB(0);



		  base_speed1=-129;

		  break;

	  default:
		  LED_RGB(7);
		  base_speed1=0;


		  break;

	  }
}

//void mapFirstLayer() {
//	stop_flag = 0;
//	base_speed1 = 80;
//	flag();
//}
//
//void mapSecondLayer() {
//	stop_flag = 0;
//	base_speed1 = 0;
//
//	flag();
//}
//
//void mapThirdSeLayer() {
//	stop_flag = 0;
//	base_speed1 = 100;
//
//	flag();
//}


//void loop(){
//    while (1)
//    {
//        ButtonPress();
//
//        if(!mode_processed){
//            switch (mode)
//            {
//            case 1:
//                base_speed1 = 0;
//                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);//R_2-2
//                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);//G_2-3
//                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);//B_2-4
//
//                calibrate_sensors();
//
//                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);//R_2-2
//                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);//G_2-3
//                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);//B_2-4
//
//                break;
//
//            case 2:
//            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);//G_1-4
//            	HAL_Delay(200);
//                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);//G_1-4
//
//                mapFirstLayer();
//
//                break;
//
//            case 3:
//            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);//G_1-4
//            	HAL_Delay(200);
//                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);//G_1-4
//
//                mapSecondLayer();
//
//                break;
//
//            case 4:
//            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);//G_1-4
//            	HAL_Delay(200);
//                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);//G_1-4
//                mapThirdSeLayer();
//                break;
//
//            default:
//                break;
//            }
//            mode_processed = 1;
//        }
//         if (mode == 2){
//        	 SpeedControl_NoENC();
//			  readSens();
//			  readSens2();
//
//
//        	 flag();
//
//           } else if (mode >= 3) {
//          	 SpeedControl_NoENC();
//			  readSens();
//			  readSens2();
//
//          	 flag();
//           }
//
//
//    }
//}
