#include "some.h"

//SW2 PB15 SW1 PC13


void ButtonPress(void){
    if (HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) == GPIO_PIN_RESET)//SW1
    {
        HAL_Delay(200);
        mode++;
        mode_processed = 0;
    }

    if (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15) == GPIO_PIN_RESET)//SW2
    {
        HAL_Delay(200);
    }

}


void mapFirstLayer() {
	stop_flag = 0;
	target_speed = 30;
	flag();
}

void mapSecondLayer() {
	stop_flag = 0;
	target_speed = 50;
	flag();
}

void mapThirdSeLayer() {
	stop_flag = 0;
	target_speed = 80;
	flag();
}


void loop(){
    while (1)
    {
        ButtonPress();
    
        if(!mode_processed){
            switch (mode)
            {
            case 1:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);//LED1
                target_speed = 0;
                calibrate_sensors();
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);//LED1
                break;

            case 2:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);//LED1
                mapFirstLayer();
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);//LED1           
            
            case 3:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);//LED1
                mapSecondLayer();
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);//LED1

            case 4:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);//LED1
                mapThirdSeLayer();
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);//LED1

            default:
                break;
            }
            mode_processed = 1;
        }
         if (mode == 2){

           flag();
           
           } else if (mode >= 3) {

           flag();
           }

        
    }
}
