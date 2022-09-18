/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Datatransmit.h"
#include "motor.h"
#include "pid.h"
#include "stdio.h"
#include "ServoAction.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define firstspeed 20//默认初始速度
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
 int mode_flag;
 int run_flag;
 float Distance[3]={0};
 float CarAngle[3]={0};
 int Cnt_1 = 0;
 int Cnt_2 = 0;
 int delta_speed=0;
 float f,g,k;
 int x=0,y=0,w=0;
 short line_x,line_y;
 int output;
 float kp1=-0.5,kp2=-0.5,kp3=-0.5;
 short Laji_x,Laji_y,Laji;
 char Distance_SendBuf[200];
 char JY901_Data_SendBuf[200];
 int add=0;
 int flag=0;
 int control_gar =0;
 
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM8_Init();
  MX_TIM12_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USART6_UART_Init();
  MX_TIM5_Init();
  MX_TIM9_Init();
  MX_TIM10_Init();
  MX_TIM11_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);

HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);
HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_2);
HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_3);
HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_4);
HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);
HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_2);

HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_ALL);
HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
User_USART_MPU6050_Init(&JY901_data);
User_USART_HC05_Init(&HC05_data);
User_USART_TFminiS_Init(&TFminiS_data);
User_USART_OPENMV_Init(&OPENMV_data);
User_USART_V831_Init(&V831_data);
HAL_TIM_Base_Start(&htim10); //定时器计数开�?
HAL_TIM_Base_Start(&htim11);
__HAL_TIM_ENABLE_IT(&htim10,TIM_IT_UPDATE);
__HAL_TIM_ENABLE_IT(&htim11,TIM_IT_UPDATE);
HAL_TIM_IC_Start_IT(&htim10, TIM_CHANNEL_1);//定时器输入捕获中断使�?
HAL_TIM_IC_Start_IT(&htim11, TIM_CHANNEL_1);
HAL_TIM_Base_Start_IT(&htim6);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		Measure();
		HMI_Send_JY901Data();
		HMI_Send_Distance();
		HMI_Send_Mode();
		if(control_gar == 1)
		{
	     char V831_Data_Buff[200];
		 sprintf (V831_Data_Buff,"page3.t4.txt=\"怡宝水瓶\"");
		 HMI_SendString(V831_Data_Buff);
	     HMI_SendBit(0xff);
	     memset( V831_Data_Buff,0,sizeof(V831_Data_Buff));
		}
		if(control_gar == 2)
		{
	     char V831_Data_Buff[200];
		 sprintf (V831_Data_Buff,"page3.t4.txt=\"农夫水瓶\"");
		 HMI_SendString(V831_Data_Buff);
	     HMI_SendBit(0xff);
	     memset( V831_Data_Buff,0,sizeof(V831_Data_Buff));
		}
		if(control_gar == 3)
		{
	     char V831_Data_Buff[200];
		 sprintf (V831_Data_Buff,"page3.t4.txt=\"纸团\"");
		 HMI_SendString(V831_Data_Buff);
	     HMI_SendBit(0xff);
	     memset( V831_Data_Buff,0,sizeof(V831_Data_Buff));
		}
		if(control_gar == 4)
		{
	     char V831_Data_Buff[200];
		 sprintf (V831_Data_Buff,"page3.t4.txt=\"纸杯\"");
		 HMI_SendString(V831_Data_Buff);
	     HMI_SendBit(0xff);
	     memset( V831_Data_Buff,0,sizeof(V831_Data_Buff));
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */



//	  HAL_Delay(2000);
//	  Grab2();
//	  HAL_Delay(2000);
//	  Grab1();
//	  HAL_Delay(2000);
//	  Claw_Close();
//	  HAL_Delay(2000);
//	  ServoUp();
//	  HAL_Delay(2000);
if(flag){
									if(add<=90)
										{
											Grab(100+add);
											add+=1;
										}
									else if(add>90)
									{
									Claw_Close();
									ServoUp();
									add=0;
									flag=0;
									Laji=0;
									}}
HAL_Delay(20);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 {
if(htim->Instance==htim6.Instance)
	{		//if(add<=90)
//										{
//											Grab(100+add);
//											add+=1;
//										}
//									else if(add>90)
//									{
//									Claw_Close();
//									ServoUp();
//									}
		switch(mode_flag)
		{	case 0: motor_stop();Mcnamu(0,0,0);ServoInit();break;
			case 1:{
					if(Distance[1]>20&&Distance[0]>20&&Distance[2]>20)
					{
							Mcnamu(0,20,0);		
								
					}
					else if(Distance[1]<20&&Distance[0]>20&&Distance[2]>20)
					{	
						if(Distance[0]>Distance[2])
						{
							Mcnamu(0,0,-20);			
										
						}
						else if(Distance[0]<Distance[2])
						{
							Mcnamu(0,0,20);
						}
					}
					else if (Distance[0]<20)
					{
						Mcnamu(0,0,20);
					}
					else if (Distance[1]<20)
					{
						Mcnamu(0,0,-20);
					}
								
					}break;//避障
			case 2:{
							if(Distance[1]<10)
							Mcnamu(0,5*(Distance[1]-10),0);
							else if(Distance[1]>13&&Distance[1]<33)
							Mcnamu(0,3*(Distance[1]-13),0);
							else if(Distance[1]>10&&Distance[1]<13)
							{Mcnamu(0,0,0);motor_stop();}
							else if(Distance[1]>33)
								Mcnamu(0,20,0);

			
			
							}break;//跟随
			case 3:{
						if(line_x!=0)
						{output=kp1*line_y/line_x+kp2*line_x;
						 Mcnamu(0,-40,output);}
						if(line_x==0)
						{output=kp3*line_y;
						 Mcnamu(output,-40,0);}
							 
							
			
							}break;//循迹
			case 4:{switch(run_flag)
							{
									case 0:{
													
														Mcnamu(0,0,0);
														delta_speed=0;
													}break;
									case 1:{	
														
														
														Mcnamu(0,firstspeed+delta_speed,0);
														delta_speed+=10;
													}break;
									case 2:{
													
														Mcnamu(0,-firstspeed+delta_speed,0);
														delta_speed-=10;
													}break;
									case 3:{
														
														Mcnamu(30,0,0);
													}break;
									case 4:{
													
														Mcnamu(-30,0,0);
													}break;
									case 6:{
														Mcnamu(0,0,20);
											}break;
									case 5:{
														Mcnamu(0,0,-20);
											}break;
							}
							
			
			
							}break;//遥控
		case 5:{	if(Laji){

							if(Distance[1]<10)
								Mcnamu(0,3*(Distance[1]-10),0);
							else if(Distance[1]>13&&Distance[1]<33)
								Mcnamu(0,3*(Distance[1]-13),0);
							else if(Distance[1]>10&&Distance[1]<13)
								{
									Mcnamu(0,0,0);
									motor_stop();
									flag=1;
								}
							else if(Distance[1]>33)
								Mcnamu(0,20,0);
			}

		}break;
		}
	}
	if (htim->Instance == htim10.Instance)  /* 定时器（超声波）溢出中断回调函数 */
	{
		Cnt_1++;
		HAL_TIM_Base_Start(&htim10);
	}
	if (htim->Instance == htim11.Instance)  /* 定时器（超声波）溢出中断回调函数 */
	{
		Cnt_2++;
		HAL_TIM_Base_Start(&htim11);
	}
 }
 
 
 
 uint8_t Edge_1 = 0;
 uint32_t T1_1;
 uint32_t T2_1;
 uint32_t T_1;
 
 uint8_t Edge_2 = 0;
 uint32_t T1_2;
 uint32_t T2_2;
 uint32_t T_2;
 /* 定时器输入捕获中断回调函�? */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if ((htim->Instance == htim10.Instance)&&htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		 if (Edge_1 == 0)
		 {
			 T1_1 = HAL_TIM_ReadCapturedValue(&htim10,TIM_CHANNEL_1);
			 
			 __HAL_TIM_SET_CAPTUREPOLARITY(&htim10,TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_FALLING);
			 
			 Edge_1 = 1;
			 
			 Cnt_1 = 0;
		 }
		 else if (Edge_1 ==1)
		 {
			 T2_1 = HAL_TIM_ReadCapturedValue(&htim10,TIM_CHANNEL_1);
			 
			 __HAL_TIM_SET_CAPTUREPOLARITY(&htim10,TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_RISING);
			 
			 Edge_1 = 0;
			 
			 T2_1 += 65535 * Cnt_1;
			 
			 T_1 = T2_1 - T1_1;
			 
			 Distance[0] = T_1 * 0.000001 * 170 * 100;  
		 }
	 }
	if ((htim->Instance == htim11.Instance)&&htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		 if (Edge_2 == 0)
		 {
			 T1_2 = HAL_TIM_ReadCapturedValue(&htim11,TIM_CHANNEL_1);
			 
			 __HAL_TIM_SET_CAPTUREPOLARITY(&htim11,TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_FALLING);
			 
			 Edge_2 = 1;
			 
			 Cnt_2 = 0;
		 }
		 else if (Edge_2 ==1)
		 {
			 T2_2 = HAL_TIM_ReadCapturedValue(&htim11,TIM_CHANNEL_1);
			 
			 __HAL_TIM_SET_CAPTUREPOLARITY(&htim11,TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_RISING);
			 
			 Edge_2 = 0;
			 
			 T2_2 += 65535 * Cnt_2;
			 
			 T_2 = T2_2 - T1_2;
			 
			 Distance[2] = T_2 * 0.000001 * 170 * 100;  
		 }
		 
	}
}
void Measure(void)
{
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_11,GPIO_PIN_SET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_8,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_11,GPIO_PIN_RESET);
}

int fputc(int ch, FILE*f)
{
	HAL_UART_Transmit(&huart6,(uint8_t*)ch,1,HAL_MAX_DELAY);
	return ch;
}

void HMI_SendBit(uint8_t k)		        
{		 
	uint8_t i;
	 for(i=0;i<3;i++)
	 {
		if(k!=0)
			{
				HAL_UART_Transmit(&huart6, &k, sizeof(k), HAL_MAX_DELAY);  
			}
	 else 
			return ;

	 } 
} 
void HMI_SendString(char *str)
{
	unsigned int k=0;
  do 
  {
      HAL_UART_Transmit(&huart6,(uint8_t *)(str + k) ,1,1000);
      k++;
  } while(*(str + k)!='\0');
  
}
void HMI_Send_JY901Data(void)
{
	
	sprintf (JY901_Data_SendBuf,"page0.t6.txt=\"%.2f\"",CarAngle[2]);
	HMI_SendString(JY901_Data_SendBuf);
	HMI_SendBit(0xff);
	memset( JY901_Data_SendBuf,0,sizeof(JY901_Data_SendBuf));
	
	sprintf (JY901_Data_SendBuf,"page0.t7.txt=\"%.2f\"",CarAngle[1]);
	HMI_SendString(JY901_Data_SendBuf);
	HMI_SendBit(0xff);
	memset( JY901_Data_SendBuf,0,sizeof(JY901_Data_SendBuf));
	
	sprintf (JY901_Data_SendBuf,"page0.t8.txt=\"%.2f\"",CarAngle[0]);
	HMI_SendString(JY901_Data_SendBuf);
	HMI_SendBit(0xff);
	memset( JY901_Data_SendBuf,0,sizeof(JY901_Data_SendBuf));
	
}

void HMI_Send_Distance(void)
{

	
	sprintf (Distance_SendBuf,"page1.t4.txt=\"%.2f\"",Distance[0]);
	HMI_SendString(Distance_SendBuf);
	HMI_SendBit(0xff);
	memset(Distance_SendBuf,0,sizeof(Distance_SendBuf));
	
	sprintf (Distance_SendBuf,"page1.t5.txt=\"%.2f\"",Distance[1]);
	HMI_SendString(Distance_SendBuf);
	HMI_SendBit(0xff);
	memset(Distance_SendBuf,0,sizeof(Distance_SendBuf));
	
	sprintf (Distance_SendBuf,"page1.t6.txt=\"%.2f\"",Distance[2]);
	HMI_SendString(Distance_SendBuf);
	HMI_SendBit(0xff);
	memset(Distance_SendBuf,0,sizeof(Distance_SendBuf));
}

void HMI_Send_Mode(void)
{
	char Mode_DataBuff[200];
	if (mode_flag == 1)
	{
		sprintf(Mode_DataBuff,"page0.t5.txt=\"避障模式\"");
		HMI_SendString(Mode_DataBuff);
		HMI_SendBit(0xff);
		memset(Mode_DataBuff,0,sizeof(Mode_DataBuff));
	}
	if (mode_flag == 2)
	{
		sprintf(Mode_DataBuff,"page0.t5.txt=\"跟随模式\"");
		HMI_SendString(Mode_DataBuff);
		HMI_SendBit(0xff);
		memset(Mode_DataBuff,0,sizeof(Mode_DataBuff));
	}
	if (mode_flag == 3)
	{
		sprintf(Mode_DataBuff,"page0.t5.txt=\"循迹模式\"");
		HMI_SendString(Mode_DataBuff);
		HMI_SendBit(0xff);
		memset(Mode_DataBuff,0,sizeof(Mode_DataBuff));
	}
	if (mode_flag == 4)
	{
		sprintf(Mode_DataBuff,"page0.t5.txt=\"遥控模式\"");
		HMI_SendString(Mode_DataBuff);
		HMI_SendBit(0xff);
		memset(Mode_DataBuff,0,sizeof(Mode_DataBuff));
	}	
	if (mode_flag == 5)
	{
		sprintf(Mode_DataBuff,"page0.t5.txt=\"垃圾分拣\"");
		HMI_SendString(Mode_DataBuff);
		HMI_SendBit(0xff);
		memset(Mode_DataBuff,0,sizeof(Mode_DataBuff));
	}	
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

