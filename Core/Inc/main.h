/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SW1_GPIO_IN_Pin GPIO_PIN_13
#define SW1_GPIO_IN_GPIO_Port GPIOC
#define SIDE_SENSOR_R_GPIO_IN_Pin GPIO_PIN_15
#define SIDE_SENSOR_R_GPIO_IN_GPIO_Port GPIOC
#define LINE_Sens13_ADC1_in11_Pin GPIO_PIN_1
#define LINE_Sens13_ADC1_in11_GPIO_Port GPIOC
#define LINE_Sens12_ADC1_in12_Pin GPIO_PIN_2
#define LINE_Sens12_ADC1_in12_GPIO_Port GPIOC
#define LINE_Sens11_ADC1_in13_Pin GPIO_PIN_3
#define LINE_Sens11_ADC1_in13_GPIO_Port GPIOC
#define LINE_Sens10_ADC1_in0_Pin GPIO_PIN_0
#define LINE_Sens10_ADC1_in0_GPIO_Port GPIOA
#define LINE_Sens9_ADC1_in1_Pin GPIO_PIN_1
#define LINE_Sens9_ADC1_in1_GPIO_Port GPIOA
#define LINE_Sens8_ADC1_in2_Pin GPIO_PIN_2
#define LINE_Sens8_ADC1_in2_GPIO_Port GPIOA
#define LINE_Sens7_ADC1_in3_Pin GPIO_PIN_3
#define LINE_Sens7_ADC1_in3_GPIO_Port GPIOA
#define LINE_Sens6_ADC1_in4_Pin GPIO_PIN_4
#define LINE_Sens6_ADC1_in4_GPIO_Port GPIOA
#define LINE_Sens5_ADC1_in5_Pin GPIO_PIN_5
#define LINE_Sens5_ADC1_in5_GPIO_Port GPIOA
#define ENC1_6_TIM3_CH1_Pin GPIO_PIN_6
#define ENC1_6_TIM3_CH1_GPIO_Port GPIOA
#define ENC1_8_TIM3_CH2_Pin GPIO_PIN_7
#define ENC1_8_TIM3_CH2_GPIO_Port GPIOA
#define LINE_Sens4_ADC1_in14_Pin GPIO_PIN_4
#define LINE_Sens4_ADC1_in14_GPIO_Port GPIOC
#define LINE_Sens3_ADC1_in15_Pin GPIO_PIN_5
#define LINE_Sens3_ADC1_in15_GPIO_Port GPIOC
#define LINE_Sens2_ADC1_in8_Pin GPIO_PIN_0
#define LINE_Sens2_ADC1_in8_GPIO_Port GPIOB
#define LINE_Sens1_ADC1_in9_Pin GPIO_PIN_1
#define LINE_Sens1_ADC1_in9_GPIO_Port GPIOB
#define SIDE_SENSOR_L_GPIO_IN_Pin GPIO_PIN_2
#define SIDE_SENSOR_L_GPIO_IN_GPIO_Port GPIOB
#define fan_PWM_1_TIM2_CH3_Pin GPIO_PIN_10
#define fan_PWM_1_TIM2_CH3_GPIO_Port GPIOB
#define LED2_ARGB3_GPIO_OUT_Pin GPIO_PIN_12
#define LED2_ARGB3_GPIO_OUT_GPIO_Port GPIOB
#define LED2_ARGB4_GPIO_OUT_Pin GPIO_PIN_13
#define LED2_ARGB4_GPIO_OUT_GPIO_Port GPIOB
#define LED2_ARGB2_GPIO_OUT_Pin GPIO_PIN_14
#define LED2_ARGB2_GPIO_OUT_GPIO_Port GPIOB
#define SW2_GPIO_IN_Pin GPIO_PIN_15
#define SW2_GPIO_IN_GPIO_Port GPIOB
#define DRVL_IN2_GPIO_Pin GPIO_PIN_8
#define DRVL_IN2_GPIO_GPIO_Port GPIOC
#define DRVL_IN1_TIM8_CH4_Pin GPIO_PIN_9
#define DRVL_IN1_TIM8_CH4_GPIO_Port GPIOC
#define DRVR_IN2_GPIO_OUT_Pin GPIO_PIN_8
#define DRVR_IN2_GPIO_OUT_GPIO_Port GPIOA
#define DRVR_IN1_TIM1_CH2_Pin GPIO_PIN_9
#define DRVR_IN1_TIM1_CH2_GPIO_Port GPIOA
#define LED3_GPIO_OUT_Pin GPIO_PIN_10
#define LED3_GPIO_OUT_GPIO_Port GPIOA
#define LED2_GPIO_OUT_Pin GPIO_PIN_11
#define LED2_GPIO_OUT_GPIO_Port GPIOA
#define LED1_GPIO_OUT_Pin GPIO_PIN_12
#define LED1_GPIO_OUT_GPIO_Port GPIOA
#define LED_ARGB3_GPIO_OUT_Pin GPIO_PIN_15
#define LED_ARGB3_GPIO_OUT_GPIO_Port GPIOA
#define NCS_GPIO_OUT_Pin GPIO_PIN_2
#define NCS_GPIO_OUT_GPIO_Port GPIOD
#define LED_ARGB4_GPIO_OUT_Pin GPIO_PIN_4
#define LED_ARGB4_GPIO_OUT_GPIO_Port GPIOB
#define LED_ARGB2_GPIO_OUT_Pin GPIO_PIN_5
#define LED_ARGB2_GPIO_OUT_GPIO_Port GPIOB
#define ENC2_8_TIM4_CH1_Pin GPIO_PIN_6
#define ENC2_8_TIM4_CH1_GPIO_Port GPIOB
#define ENC2_6_TIM4_CH2_Pin GPIO_PIN_7
#define ENC2_6_TIM4_CH2_GPIO_Port GPIOB
#define LCD_3_I2C1_SCL_Pin GPIO_PIN_8
#define LCD_3_I2C1_SCL_GPIO_Port GPIOB
#define LCD2_I2C1_SDA_Pin GPIO_PIN_9
#define LCD2_I2C1_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
