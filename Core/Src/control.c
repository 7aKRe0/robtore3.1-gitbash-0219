#include "some.h"




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
		if(Line1_sens[i] >= max_white_a[i]){
			Line1_sens[i] = max_white_a[i];
		}
		if(Line1_sens[i] <= min_black_a[i]){
			Line1_sens[i] = min_black_a[i];
		}
		float range_a = max_white_a[i] - min_black_a[i];
		if(range_a == 0){
			range_a = 1;
		}

		Line1_sum += (Line1_sens[i]*g1[i])*1000/ range_a;
	}

	for (int i = 0; i < SENSOR_COUNT; i++){
		if(Line2_sens[i] >= max_white_b[i]){
			Line2_sens[i] = max_white_b[i];
		}
		if(Line2_sens[i] <= min_black_b[i]){
			Line2_sens[i] = min_black_b[i];
		}
		float range_b = max_white_b[i] - min_black_b[i];
		if(range_b == 0){
			range_b = 1;
		}

		Line2_sum += (Line2_sens[i]*g2[i])*1000/range_b;
	}

	return  Line1_sum - Line2_sum;


}

void SpeedControl() {
	//kari
	static uint32_t last_time = 0;
	uint32_t current_time = HAL_GetTick();
	float dt = (current_time - last_time) / 1000.0;
	last_time = current_time;

	if (dt < 0.001){
		dt = 0.001;
	}
	//kokomade


    float error = calculateError();
    // PD
    float derivative = (error - previous_error) / dt;

    float P =Kp * error;
    float D =Kd * derivative;

    float output = P + D;
    previous_error = error;

    target_speed_L = base_speed - output;
    target_speed_R = base_speed + output;

	calculateEncoderSpeed(dt);//encoder PRG
	//speed_error
	float adjusted_speed_L = target_speed_L -current_speed_L;
	float adjusted_speed_R = target_speed_R -current_speed_R;

    static float previous_speed_error_L = 0, previous_speed_error_R = 0;
    float speed_derivative_L = (adjusted_speed_L - previous_speed_error_L) / dt;
    float speed_derivative_R = (adjusted_speed_R - previous_speed_error_R) / dt;


	//P
	float speed_L_P_gain = Sp * adjusted_speed_L;
	float speed_R_P_gain = Sp * adjusted_speed_R;
	//D
    float speed_L_D_gain = Sd * speed_derivative_L;
    float speed_R_D_gain = Sd * speed_derivative_R;
    

	float duty_L = speed_L_P_gain + speed_L_D_gain;
    float duty_R = speed_R_P_gain + speed_R_D_gain;

    if (duty_L > 4000) duty_L = 4000;
    if (duty_L < -4000) duty_L = -4000;
    if (duty_R > 4000) duty_R = 4000;
    if (duty_R < -4000) duty_R = -4000;

    previous_speed_error_L = adjusted_speed_L;
    previous_speed_error_R = adjusted_speed_R;
    // モータ
    ControlMotor(duty_L, duty_R);
}

//   HAL_TIM_Encoder_Start_IT( &htim3,TIM_CHANNEL_ALL);//ENC1
//   HAL_TIM_Encoder_Start_IT( &htim4,TIM_CHANNEL_ALL);//ENC2
void calculateEncoderSpeed(float dt){
	static int32_t cnt_old_L = 0, cnt_old_R = 0;

	int32_t cnt_new_L = __HAL_TIM_GET_COUNTER(&htim4);
	int32_t cnt_new_R = __HAL_TIM_GET_COUNTER(&htim3);

	int32_t cnt_L = cnt_new_L - cnt_old_L;
	int32_t cnt_R = cnt_new_R - cnt_old_R;
	cnt_old_L = cnt_new_L;
    cnt_old_R = cnt_new_R;

	if (cnt_L > 32768) cnt_L -= 65536;
	if (cnt_L < -32768) cnt_L += 65536;
	if (cnt_R > 32768) cnt_R -= 65536;
	if (cnt_R < -32768) cnt_R += 65536;


	float wheel_circumference = M_PI * TIRE;
	current_speed_L = (wheel_circumference * cnt_L) / (ENCODER_CPR * dt);
	current_speed_R = (wheel_circumference * cnt_R) / (ENCODER_CPR * dt);


}
