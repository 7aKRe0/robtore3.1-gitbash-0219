#ifndef TEST_H
#define TEST_H

#include <stdint.h>  // uint16_t, uint32_t
#include "main.h"

#define SENSOR_COUNT 6
#define dt 0.01
#define TIRE 22
#define ENCODER_CPR 2048  //  CPR のエンコーダを使用(kari)


#ifndef M_PI
#define M_PI 3.1415926535
#endif


extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

extern I2C_HandleTypeDef hi2c1;

extern SPI_HandleTypeDef hspi3;


extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;

extern UART_HandleTypeDef huart6;

extern float previous_speed_error_L;
extern float previous_speed_error_R;

extern int mode;
extern int mode_processed;

// extern float base_speed;
extern float Kp, Ki, Kd ,Sp, Si, Sd;
extern float previous_error, integral;
extern float target_speed;
extern float current_speed_L, current_speed_R;
extern float side_r_flag, side_l_flag;
extern float side_l_time, side_r_time;
extern float stop_flag;
extern uint16_t Line_sens[13];
extern uint16_t side_sens[2];
extern float Line1_sens[SENSOR_COUNT];
extern float Line2_sens[SENSOR_COUNT];
extern float Line3_sens[2];
extern float cross_time;


extern float max_white_a[SENSOR_COUNT];
extern float min_black_a[SENSOR_COUNT];

extern float max_white_b[SENSOR_COUNT];
extern float min_black_b[SENSOR_COUNT];

extern float threshold_0, threshold_1;

extern float min_black_0, min_black_1;

extern float max_white_0;
extern float max_white_1;

void readSens(void);
void readSens2(void);
void controlMotor(double duty_L, double duty_R);
void calculateEncoderSpeed();



#endif // TEST_H
