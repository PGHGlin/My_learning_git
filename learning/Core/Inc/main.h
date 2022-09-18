/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void Measure(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SERVO5_Pin GPIO_PIN_5
#define SERVO5_GPIO_Port GPIOE
#define ECHO_LEFT_Pin GPIO_PIN_6
#define ECHO_LEFT_GPIO_Port GPIOF
#define ECHO_RIGHT_Pin GPIO_PIN_7
#define ECHO_RIGHT_GPIO_Port GPIOF
#define TRIG_LEFT_Pin GPIO_PIN_8
#define TRIG_LEFT_GPIO_Port GPIOF
#define SERVO1_Pin GPIO_PIN_0
#define SERVO1_GPIO_Port GPIOA
#define SERVO2_Pin GPIO_PIN_1
#define SERVO2_GPIO_Port GPIOA
#define SERVO3_Pin GPIO_PIN_2
#define SERVO3_GPIO_Port GPIOA
#define SERVO4_Pin GPIO_PIN_3
#define SERVO4_GPIO_Port GPIOA
#define ENCODER_A_A_Pin GPIO_PIN_5
#define ENCODER_A_A_GPIO_Port GPIOA
#define ENCODER_B_A_Pin GPIO_PIN_6
#define ENCODER_B_A_GPIO_Port GPIOA
#define ENCODER_B_B_Pin GPIO_PIN_7
#define ENCODER_B_B_GPIO_Port GPIOA
#define TRIG_RIGHT_Pin GPIO_PIN_11
#define TRIG_RIGHT_GPIO_Port GPIOF
#define DIN_1_Pin GPIO_PIN_8
#define DIN_1_GPIO_Port GPIOE
#define ENCODER_D_B_Pin GPIO_PIN_11
#define ENCODER_D_B_GPIO_Port GPIOE
#define SERVO6_Pin GPIO_PIN_14
#define SERVO6_GPIO_Port GPIOB
#define LAJI_DOCK_TX_Pin GPIO_PIN_8
#define LAJI_DOCK_TX_GPIO_Port GPIOD
#define LAJI_DOCK_RX_Pin GPIO_PIN_9
#define LAJI_DOCK_RX_GPIO_Port GPIOD
#define ENCODER_C_B_Pin GPIO_PIN_12
#define ENCODER_C_B_GPIO_Port GPIOD
#define ENCODER_C_A_Pin GPIO_PIN_13
#define ENCODER_C_A_GPIO_Port GPIOD
#define BIN_1_Pin GPIO_PIN_6
#define BIN_1_GPIO_Port GPIOG
#define AIN_2_Pin GPIO_PIN_7
#define AIN_2_GPIO_Port GPIOG
#define AIN_1_Pin GPIO_PIN_8
#define AIN_1_GPIO_Port GPIOG
#define PWMA_Pin GPIO_PIN_6
#define PWMA_GPIO_Port GPIOC
#define PWMB_Pin GPIO_PIN_7
#define PWMB_GPIO_Port GPIOC
#define PWMC_Pin GPIO_PIN_8
#define PWMC_GPIO_Port GPIOC
#define PWMD_Pin GPIO_PIN_9
#define PWMD_GPIO_Port GPIOC
#define ENCODER_D_A_Pin GPIO_PIN_8
#define ENCODER_D_A_GPIO_Port GPIOA
#define XUNXIAN_DOCK_TX_Pin GPIO_PIN_9
#define XUNXIAN_DOCK_TX_GPIO_Port GPIOA
#define XUNXIAN_DOCK_RX_Pin GPIO_PIN_10
#define XUNXIAN_DOCK_RX_GPIO_Port GPIOA
#define HC05_TX_Pin GPIO_PIN_10
#define HC05_TX_GPIO_Port GPIOC
#define HC05_RX_Pin GPIO_PIN_11
#define HC05_RX_GPIO_Port GPIOC
#define JY901_TX_Pin GPIO_PIN_12
#define JY901_TX_GPIO_Port GPIOC
#define JY901_RX_Pin GPIO_PIN_2
#define JY901_RX_GPIO_Port GPIOD
#define DIN_2_Pin GPIO_PIN_3
#define DIN_2_GPIO_Port GPIOD
#define CIN_1_Pin GPIO_PIN_4
#define CIN_1_GPIO_Port GPIOD
#define TF_TX_Pin GPIO_PIN_5
#define TF_TX_GPIO_Port GPIOD
#define TF_RX_Pin GPIO_PIN_6
#define TF_RX_GPIO_Port GPIOD
#define BIN_2_Pin GPIO_PIN_7
#define BIN_2_GPIO_Port GPIOD
#define HMI_RX_Pin GPIO_PIN_9
#define HMI_RX_GPIO_Port GPIOG
#define HMI_TX_Pin GPIO_PIN_14
#define HMI_TX_GPIO_Port GPIOG
#define CIN_2_Pin GPIO_PIN_15
#define CIN_2_GPIO_Port GPIOG
#define ENCODER_A_B_Pin GPIO_PIN_3
#define ENCODER_A_B_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
extern int run_flag;
extern int mode_flag;
extern float Distance[3];
extern float CarAngle[3];
void HMI_Send_JY901Data(void);
void HMI_SendString(char *str);
void HMI_Send_Distance(void);
void HMI_SendBit(uint8_t k);
void HMI_Send_Mode(void);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
