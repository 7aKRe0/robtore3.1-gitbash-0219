/*
 * sensor.h
 *
 *  Created on: Mar 5, 2025
 *      Author: uchuu
 */

#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

#define SENSOR_COUNT 13

#define MAX_RECORDS 1000 //10000


//sens
extern uint16_t Line_sens[13];

extern float Line1_sens[SENSOR_COUNT];
extern float Line2_sens[SENSOR_COUNT];
extern float Line3_sens[2];
extern float  Line1_min[SENSOR_COUNT];
extern float Line1_max[SENSOR_COUNT];
extern float Line2_min[SENSOR_COUNT];
extern float Line2_max[SENSOR_COUNT];



//calibrate
extern float threshold_0, threshold_1;
extern float min_black_0, min_black_1;
extern float max_white_0;
extern float max_white_1;



//SpeedControl
extern float Kp, Ki, Kd ,Sp, Si, Sd;
extern float target_speed;
extern float previous_speed_error_L;
extern float previous_speed_error_R;
extern float base_speed1;
extern float previous_error, integral;
extern float current_speed_L, current_speed_R;
extern float accumulation;



//cross
extern float side_r_flag, side_l_flag;
extern float side_l_time, side_r_time;
extern float stop_flag;
extern uint16_t side_sens[2];
extern float cross_time;
extern int cross_flag;
extern float average_cross;
extern uint32_t start_time;
extern uint16_t test_flag;
extern int32_t cnt_L;


//VelocityPlan
//#define MAX_RECORDS 100
extern int32_t VP_L[MAX_RECORDS];
extern int32_t VP_R[MAX_RECORDS];
extern uint16_t index ;


void readSens(void);
void readSens2(void);
void calibrate_sensors();
void SpeedControl_NoENC();
float calculateEncoderSpeed();
void flag();
float sens_get(void);
float  EncoderSpeed();
void	VelocityPlan();



#endif /* INC_SENSOR_H_ */
