#include "some.h"

//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);//LED1
//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);//LED2
//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);//LED3
//
//
//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);//R_1-2
//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);//G_1-4
//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);//B_1-3
//
//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);//R_2-2
//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);//G_2-4
//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);//B_2-3


void LED_RGB(int i){

	switch (i)
	            {
	            case 1://R
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);//R_1-2
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);//G_1-4
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);//B_1-3

	                break;

	            case 2://G
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);//R_1-2
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);//G_1-4
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);//B_1-3

	                break;

	            case 3://B
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);//R_1-2
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);//G_1-4
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);//B_1-3

	                break;

	            case 4://y
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);//R_1-2
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);//G_1-4
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);//B_1-3

	                break;

	            case 5://pink
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);//R_1-2
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);//G_1-4
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);//B_1-3

	                break;

	            case 6://white
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);//R_1-2
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);//G_1-4
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);//B_1-3

	                break;

	            case 7://Cyan
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);//R_1-2
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);//G_1-4
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);//B_1-3

	                break;

	            default:
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);//R_1-2
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);//G_1-4
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);//B_1-3
	                break;
	            }


}

void LED_RGB_2(int n){

	switch (n)
	            {
	            case 1://R
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);//R_2-2
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);//G_2-4
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);//B_2-3

	                break;

	            case 2://G
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);//R_2-2
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);//G_2-4
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);//B_2-3
	                break;

	            case 3://B
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);//R_2-2
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);//G_2-4
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);//B_2-3
	                break;

	            case 4://y
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);//R_2-2
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);//G_2-4
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);//B_2-3

	                break;

	            case 5://pink
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);//R_2-2
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);//G_2-4
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);//B_2-3

	                break;

	            case 6://white
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);//R_2-2
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);//G_2-4
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);//B_2-3
	                break;

	            case 7://Cyan
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);//R_2-2
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);//G_2-4
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);//B_2-3

	                break;

	            default:
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);//R_2-2
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);//G_2-4
	            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);//B_2-3
	                break;
	            }


}


void LED(int i){

	switch (i)
	            {
	            case 1://1
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);//LED1
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);//LED2
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);//LED3

	                break;

	            case 2://2
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);//LED1
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);//LED2
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);//LED3

	                break;

	            case 3://3
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);//LED1
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);//LED2
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);//LED3

	                break;


	            default:
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);//LED1
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);//LED2
	            	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);//LED3
	                break;
	            }


}
