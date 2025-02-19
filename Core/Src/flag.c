#include "some.h"




uint32_t last_sens_time = 0;
uint32_t De_last,De_time = 0;

uint32_t cross_disable_time = 0;
uint32_t cross_disable_duration = 100;



void flag(void){


    if(Line3_sens[1] == 1)//L
    {
//        side_l_time = HAL_GetTick();
//        stop_flag++;



    }
    if(Line3_sens[0] == 1)
    {
//        side_r_time = HAL_GetTick();
//        side_r_flag = 1;
//		stop_flag++;


    }

//    if(side_l_flag == 1 && HAL_GetTick() - side_l_time >= cross_time &&side_r_flag == 0){
//        side_l_flag = 0;
////        stop_flag++;
//
//    }
//
//    if(side_l_flag == 1){
//        if (HAL_GetTick() - side_l_time < cross_time && side_r_flag == 1)
//        {
//            side_l_flag = 0;
//            side_r_flag = 0;
//            cross_disable_time = HAL_GetTick();
////            stop_flag++;
//
//
//        }
//
//    }
//    if (side_r_flag ==1){
//        if(HAL_GetTick() - side_r_time < cross_time && side_l_flag == 1){
//            side_l_flag = 0;
//            side_r_flag = 0;
//            cross_disable_time = HAL_GetTick();
////            stop_flag++;
//
//        }else if(HAL_GetTick() - side_r_time >= cross_time && side_l_flag == 0){
//            stop_flag++;
//            side_r_flag = 0;
//
//        }
//    }

    if(stop_flag >= 2){

    	base_speed1 = 0;
    }
    

}

