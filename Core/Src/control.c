#include "some.h"

#define REDUCTION_RATIO 0.4 // 減速比
#define DISTANCE_PER_CNT (M_PI * TIRE * REDUCTION_RATIO / ENCODER_CPR) //[mm per cnt]
float distance_1ms,distance_1ms_L,distance_1ms_R;


void ControlMotor(double duty_L, double duty_R){

    if (duty_L >= 0) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET); // PH-HIGH(+)
        __HAL_TIM_SET_COMPARE( &htim8,TIM_CHANNEL_4, duty_L);
    } else {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET); // PH-LOW(-)
        __HAL_TIM_SET_COMPARE( &htim8,TIM_CHANNEL_4, -duty_L);
    }
    if (duty_R >= 0) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET); // PH-HIGH(+)
        __HAL_TIM_SET_COMPARE( &htim1,TIM_CHANNEL_2, duty_R);
    } else {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET); // PH-LOW(-)
        __HAL_TIM_SET_COMPARE( &htim1,TIM_CHANNEL_2, -duty_R);
        }
}


float calculateError() {
	readSens();
	float Line1_sum = 0.0;
	float Line2_sum = 0.0;
	static const int g1[] = {1,1,1,1,1,1};//L
	static const int g2[] = {1,1,1,1,1,1};

	for (int i = 0; i < SENSOR_COUNT; i++){//L
		if(Line1_sens[i] >= Line1_max[i]){
			Line1_sens[i] = Line1_max[i];
		}
		if(Line1_sens[i] <= Line1_min[i]){
			Line1_sens[i] = Line1_min[i];
		}
		float range_a = Line1_max[i] - Line1_min[i];
		if(range_a == 0){
			range_a = 1;
		}

		Line1_sum += (Line1_sens[i]*g1[i])*1000/ range_a;
	}

	for (int i = 0; i < SENSOR_COUNT; i++){
		if(Line2_sens[i] >= Line2_max[i]){
			Line2_sens[i] = Line2_max[i];
		}
		if(Line2_sens[i] <= Line2_min[i]){
			Line2_sens[i] = Line2_min[i];
		}
		float range_b = Line2_max[i] - Line2_min[i];
		if(range_b == 0){
			range_b = 1;
		}

		Line2_sum += (Line2_sens[i]*g2[i])*1000/range_b;
	}

	return  -Line1_sum + Line2_sum;


}

//   HAL_TIM_Encoder_Start_IT( &htim3,TIM_CHANNEL_ALL);//ENC1
//   HAL_TIM_Encoder_Start_IT( &htim4,TIM_CHANNEL_ALL);//ENC2
void calculateEncoderSpeed(){
	static int32_t cnt_old_L = 0, cnt_old_R = 0;

	int32_t cnt_new_L = __HAL_TIM_GET_COUNTER(&htim4);
	int32_t cnt_new_R = __HAL_TIM_GET_COUNTER(&htim3);

	int32_t cnt_L = cnt_new_L - cnt_old_L;
	int32_t cnt_R = cnt_new_R - cnt_old_R;


	if (cnt_L > 32767) cnt_L -= 65536;
	if (cnt_L < -32767) cnt_L += 65536;
	if (cnt_R > 32767) cnt_R -= 65536;
	if (cnt_R < -32767) cnt_R += 65536;

	distance_1ms = DISTANCE_PER_CNT * (-cnt_L + cnt_R) / 2;
	distance_1ms_L = DISTANCE_PER_CNT * cnt_L;
	distance_1ms_R = DISTANCE_PER_CNT * cnt_R;


	if(cnt_new_L != cnt_old_L || cnt_new_R != cnt_old_R){
		char scnt[100];
		sprintf(scnt, "Speed: %f\r\n", distance_1ms);

	}
	cnt_old_L = cnt_new_L;
    cnt_old_R = cnt_new_R;
}


//void SpeedControl() {
//
//    float error = calculateError();
//    // PD
//    float derivative = (error - previous_error) / dt;
//
//    float P =Kp * error;
//    float D =Kd * derivative;
//
//    float output = P + D;
//    previous_error = error;//line
//
//	calculateEncoderSpeed();//encoder PRG
//	//speed_error
//	//target_speedを個別に決める
//	float adjusted_speed_L = target_speed - distance_1ms_L;
//	float adjusted_speed_R = target_speed - distance_1ms_R;
//
//	static float integral_L = 0, integral_R = 0;
//	integral_L += adjusted_speed_L * dt;
//	integral_R += adjusted_speed_R * dt;
//
//    static float previous_adjusted_speed_L = 0, previous_adjusted_speed_R = 0;
//    float derivative_speed_L = (adjusted_speed_L - previous_adjusted_speed_L) / dt;
//    float derivative_speed_R = (adjusted_speed_R - previous_adjusted_speed_R) / dt;
//
//	//P
//	float speed_L_P_gain = Sp * adjusted_speed_L;
//	float speed_R_P_gain = Sp * adjusted_speed_R;
//	//I
//    float speed_L_I_gain = Si * integral_L;
//    float speed_R_I_gain = Si * integral_R;
//
//
//    // D
//    float speed_L_D_gain = Sd * derivative_speed_L;
//    float speed_R_D_gain = Sd * derivative_speed_R;
//
//	#define I_LIMIT 100
//	if (integral_L > I_LIMIT) integral_L = I_LIMIT;
//	if (integral_L < -I_LIMIT) integral_L = -I_LIMIT;
//	if (integral_R > I_LIMIT) integral_R = I_LIMIT;
//	if (integral_R < -I_LIMIT) integral_R = -I_LIMIT;
//
//	float duty_L = speed_L_P_gain + speed_L_I_gain + speed_L_D_gain;
//    float duty_R = speed_R_P_gain + speed_R_I_gain + speed_R_D_gain;
//
//    if (duty_L > 4000) duty_L = 4000;
//    if (duty_L < -4000) duty_L = -4000;
//    if (duty_R > 4000) duty_R = 4000;
//    if (duty_R < -4000) duty_R = -4000;
//
//    previous_speed_error_L = adjusted_speed_L;
//    previous_speed_error_R = adjusted_speed_R;
//
//
//	float motor_L = duty_L - output;
//    float motor_R = duty_R + output;
//    // モータ
//    ControlMotor(motor_L, motor_R);
//}


//void SpeedControl_NoENC() {
//
//	     float error = calculateError();
//	     // PD
//	     float derivative = (error - previous_error) / dt;
//
//	     float P =Kp * error;
//	     float D =Kd * derivative;
//
//	     float output = P + D;
//	     previous_error = error;
//
//	     float duty_L = 80 - output;
//	     float duty_R = 80 + output;
////		     float duty_L =- output;
////		     float duty_R = output;
//
//	     float motor_L = -1*(duty_L);
//	     float motor_R = -1*(duty_R);
//
//
//
//	     if (motor_L > 499) motor_L = 499;
//	     if (motor_L < -499) motor_L = -499;
//	     if (motor_R > 499) motor_R = 499;
//	     if (motor_R < -499) motor_R = -499;
//
//	     // モータ
//	     ControlMotor(motor_L, motor_R);
//}


