#ifndef __DATATRANSMIT_H_
#define __DATATRANSMIT_H_
#include "main.h"
#include "JY901.h"
#include "stdio.h"
#include "string.h"


#define RXBUFFER_LEN_MPU6050 33
#define RXBUFFER_LEN_BLUETOOTH 8
#define RXBUFFER_LEN_V831 10
#define RXBUFFER_LEN_OPENMV 8
#define RXBUFFER_LEN_LASERRANGE 9
typedef struct
{
	float angle[3];
}Angle;

typedef struct
{
	float a[3];
}Acc;

typedef struct
{
	float w[3];
}SGyro;

typedef struct User_USART_MPU6050
{
		uint8_t Rx_flag;												
		uint8_t Rx_len;													
		uint8_t frame_head;											
		uint8_t RxBuffer[RXBUFFER_LEN_MPU6050];				
		Angle angle;
		Acc acc;
		SGyro w;
}User_USART_MPU6050;

typedef struct User_USART_BLUETOOTH
{
		uint8_t Rx_flag;												
		uint8_t Rx_len;													
		uint8_t frame_head;											
		uint8_t frame_end;
		uint8_t RxBuffer[RXBUFFER_LEN_BLUETOOTH];					
}User_USART_BLUETOOTH;

typedef struct User_USART_LASERRANGE
{
		uint8_t Rx_flag;												
		uint8_t Rx_len;													
		uint8_t frame_head;											
		uint8_t frame_end;
		uint8_t RxBuffer[RXBUFFER_LEN_LASERRANGE];					
}User_USART_LASERRANGE;

typedef struct User_USART_V831
{
		uint8_t Rx_flag;												
		uint8_t Rx_len;													
		uint8_t frame_head;											
		uint8_t frame_end;
		uint8_t RxBuffer[RXBUFFER_LEN_BLUETOOTH];					
}User_USART_V831;

typedef struct User_USART_OPENMV
{
		uint8_t Rx_flag;												
		uint8_t Rx_len;													
		uint8_t frame_head;											
		uint8_t frame_end;
		uint8_t RxBuffer[RXBUFFER_LEN_BLUETOOTH];					
}User_USART_OPENMV;

extern User_USART_BLUETOOTH HC05_data;
extern User_USART_MPU6050 JY901_data;
extern User_USART_LASERRANGE TFminiS_data;
extern User_USART_V831 V831_data;
extern User_USART_OPENMV OPENMV_data;


void JY901_Process(void);
void HC05_Process(void);
void TFminiS_Process(void);
void V831_Process(void);
void OPENMV_Process(void);

void User_USART_MPU6050_Init(User_USART_MPU6050 *Data);
void User_USART_HC05_Init(User_USART_BLUETOOTH *Data);
void User_USART_TFminiS_Init(User_USART_LASERRANGE *Data);
void User_USART_V831_Init(User_USART_V831 *Data);
void User_USART_OPENMV_Init(User_USART_OPENMV *Data);






#endif
