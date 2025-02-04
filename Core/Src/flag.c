#include "some.h"




uint32_t last_sens_time = 0;
uint32_t De_last,De_time = 0;

uint32_t cross_disable_time = 0;
uint32_t cross_disable_duration = 100;

int isSensorDisabled() {
    return (HAL_GetTick() - cross_disable_time < cross_disable_duration);
}

void flag(void){

    cross_time = 100;

    if(isSensorDisabled()){
        return;
    }
    if(Line3_sens[0] == 1)//L
    {
        side_l_time = HAL_GetTick();
        side_l_flag = 1;
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);//B_1-4


    }
    if(Line3_sens[1] == 1)
    {
        side_r_time = HAL_GetTick();
        side_r_flag = 1;
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);//R_1-2

    }

    if(side_l_flag == 1 && HAL_GetTick() - side_l_time >= cross_time &&side_r_flag == 0){
        side_l_flag = 0;
    }

    if(side_l_flag == 1){
        if (HAL_GetTick() - side_l_time < cross_time && side_r_flag == 1)
        {
            side_l_flag = 0;
            side_r_flag = 0;
            cross_disable_time = HAL_GetTick();
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);//B_1-4

        }
        
    }
    if (side_r_flag ==1){
        if(HAL_GetTick() - side_r_time < cross_time && side_l_flag == 1){
            side_l_flag = 0;
            side_r_flag = 0;
            cross_disable_time = HAL_GetTick();
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);//B_1-4
        }else if(HAL_GetTick() - side_r_time >= cross_time && side_l_flag == 0){
            stop_flag++;
            side_r_flag = 0;

        }
    }

    if(stop_flag >= 2){
    	target_speed = 0;
    }
    

}

