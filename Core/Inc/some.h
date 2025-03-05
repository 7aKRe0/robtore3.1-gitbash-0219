#ifndef TEST_H
#define TEST_H

#include <stdint.h>  // uint16_t, uint32_t
#include "main.h"
#include"math.h"
#include <stdio.h>

#include <LED.h>
#include <sensor.h>
#include <SW1.h>



//#define SENSOR_COUNT 13
#define dt 0.001
#define TIRE 22
#define ENCODER_CPR 2048  //  CPR のエンコーダを使用(kari)
#define OFFSET  10000



#ifndef M_PI
#define M_PI 3.1415926535
#endif


extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

extern I2C_HandleTypeDef hi2c1;

extern SPI_HandleTypeDef hspi3;



extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim8;

extern UART_HandleTypeDef huart6;


extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;

extern UART_HandleTypeDef huart6;





//extern float max_white_a[SENSOR_COUNT];
//extern float min_black_a[SENSOR_COUNT];
//
//extern float max_white_b[SENSOR_COUNT];
//extern float min_black_b[SENSOR_COUNT];





extern float distance_1ms,distance_1ms_L,distance_1ms_R;



//void controlMotor(double duty_L, double duty_R);
void ControlMotor(double duty_L, double duty_R);





#endif // TEST_H
