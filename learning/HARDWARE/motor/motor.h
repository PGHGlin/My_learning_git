#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "main.h"
#include "gpio.h"
#include "stdlib.h"	
#include "stm32f4xx_hal.h"

#define AIN1_0()	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_RESET)	
#define AIN1_1()	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_SET)
#define AIN2_0()	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_RESET)
#define AIN2_1()	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_SET)
#define BIN1_0()	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_RESET)
#define BIN1_1()	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET)
#define BIN2_0()	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET)
#define BIN2_1()	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_SET)
#define CIN1_0(	)	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_RESET)	
#define CIN1_1()	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_SET)
#define CIN2_0()	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_15,GPIO_PIN_RESET)
#define CIN2_1()	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_15,GPIO_PIN_SET)
#define DIN1_0()	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_RESET)
#define DIN1_1()	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_SET)
#define DIN2_0()	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,GPIO_PIN_RESET)
#define DIN2_1()	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,GPIO_PIN_SET)



void motor_stop(void);



#endif
