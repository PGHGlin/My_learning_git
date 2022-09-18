#include "Datatransmit.h"
#include "motor.h"

User_USART_MPU6050 JY901_data;
User_USART_BLUETOOTH HC05_data;
User_USART_LASERRANGE TFminiS_data;
User_USART_V831 V831_data;
User_USART_OPENMV OPENMV_data;

extern UART_HandleTypeDef huart3;
extern int mode_flag;
extern int run_flag;
extern short Laji_x,Laji_y,Laji;
extern short line_x,line_y;

struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SAngle 	stcAngle;

uint8_t a =0;



/*·····JY901九轴陀螺仪 串口接收数据帧初始化与数据处理·····*/
/**占据串口：UART_5
  *数据帧字长：RXBUFFER_LEN_MPU6050 33
	*数据帧头：0x55
**/
void User_USART_MPU6050_Init(User_USART_MPU6050 *Data)
{
		for(uint16_t i=0; i < RXBUFFER_LEN_MPU6050; i++)	Data->RxBuffer[i] = 0;
		Data->frame_head = 0x55;
		Data->Rx_flag = 0;
		Data->Rx_len = 0;
}

void JY901_Process()
{
		if(JY901_data.Rx_len < RXBUFFER_LEN_MPU6050) return;   	

		for(uint8_t i=0;i<4;i++)
		{
				if(JY901_data.RxBuffer[i*11]!= JY901_data.frame_head) continue;
				switch(JY901_data.RxBuffer[i*11+1])
				{
						case 0x51:	
							memcpy(&stcAcc,&JY901_data.RxBuffer[2 + i*11],8);
							for(uint8_t j = 0; j < 3; j++) JY901_data.acc.a[j] = (float)stcAcc.a[j]/32768*16;							
						break;
						case 0x52:	
							memcpy(&stcGyro,&JY901_data.RxBuffer[2 + i*11],8);
							for(uint8_t j = 0; j < 3; j++) JY901_data.w.w[j] = (float)stcGyro.w[j]/32768*2000;								
						break;
						case 0x53:	
							memcpy(&stcAngle,&JY901_data.RxBuffer[2 + i*11],8);
							for(uint8_t j = 0; j < 3; j++)
             {						
								JY901_data.angle.angle[j] = (float)stcAngle.Angle[j]/32768*180;
                CarAngle[j] = JY901_data.angle.angle[j];							 
						 }
							 break;
				}
				
		}

}
/*·····HC05主从一体蓝牙 串口接收数据帧初始化与数据处理·····*/
/**占据串口：UART_4
  *数据帧字长：RXBUFFER_LEN_BLUETOOTH 8
	*数据帧头：0x55
**/
void User_USART_HC05_Init(User_USART_BLUETOOTH *Data)
{
		for(uint16_t i=0; i < RXBUFFER_LEN_BLUETOOTH; i++)	Data->RxBuffer[i] = 0;
		Data->frame_head = 0x55;
		Data->frame_end =0x55;
		Data->Rx_flag = 0;
		Data->Rx_len = 0;
}
void HC05_Process()
{

	if (HC05_data.RxBuffer[0]!=HC05_data.frame_head) return;
	switch(HC05_data.RxBuffer[1])
		{	case 0x00:mode_flag=0;break;
		case 0x01:mode_flag=1;//避障模式
		break;
		case 0x02:mode_flag=2;//跟随模式
		break;
		case 0x03:mode_flag=3;//循迹模式
		break;
		case 0x05:mode_flag=5;
		break;
		case 0x04:{mode_flag=4;//遥控模式
							 switch (HC05_data.RxBuffer[2])
							 {
								 case 0x01:run_flag=1;break;//前进
								 case 0x02:run_flag=2;break;//后退
								 case 0x03:run_flag=3;break;//左平移
								 case 0x04:run_flag=4;break;//右平移
								 case 0x05:run_flag=5;break;//逆时针旋转
								 case 0x06:run_flag=6;break;//顺时针旋转
								 case 0x00:run_flag=0;motor_stop();break;//停止
							 }
						  }
		break;

							 
	}
}
/*·····TFminiS激光测距雷达 串口接收数据帧初始化与数据处理·····*/
/**占据串口：UART_2
  *数据帧字长：RXBUFFER_LEN_LASERRANGE 8
	*数据帧头：0x59
**/
void User_USART_TFminiS_Init(User_USART_LASERRANGE *Data)
{
	for(uint16_t i=0; i < RXBUFFER_LEN_LASERRANGE; i++)	Data->RxBuffer[i] = 0;
		Data->frame_head = 0x59;
		Data->Rx_flag = 0;
		Data->Rx_len = 0;
}
void TFminiS_Process(void)
{
	  uint32_t i = 0;
    uint8_t chk_cal = 0;
    

    if(TFminiS_data.Rx_len == RXBUFFER_LEN_LASERRANGE)
    {
        if((TFminiS_data.RxBuffer[0] == TFminiS_data.frame_head)&&(TFminiS_data.RxBuffer[1] == TFminiS_data.frame_head))
        {
            for(i = 0; i < (RXBUFFER_LEN_LASERRANGE - 1); i++)
            {
                chk_cal += TFminiS_data.RxBuffer[i];
            }

            if(chk_cal == TFminiS_data.RxBuffer[RXBUFFER_LEN_LASERRANGE- 1])
            {
                Distance[1] 		 = TFminiS_data.RxBuffer[2] | (TFminiS_data.RxBuffer[3] << 8);
            }
        }
    }
}
/*·····垃圾识别摄像头 串口接收数据帧初始化与数据处理·····*/
/**占据串口：UART_3
  *数据帧字长：RXBUFFER_LEN_V831 10
	*数据帧头：0x55
**/
void User_USART_V831_Init(User_USART_V831 *Data)
{
		for(uint16_t i=0; i < RXBUFFER_LEN_V831; i++)	Data->RxBuffer[i] = 0;
		Data->frame_head = 0x55;
		Data->Rx_flag = 0;
		Data->Rx_len = 0;
}

void V831_Process()
{
	  char V831_Data_Buff[200];
		if(V831_data.RxBuffer[0] != V831_data.frame_head) return;   	
		Laji=V831_data.RxBuffer[1]<<8|V831_data.RxBuffer[2];
		Laji_x=V831_data.RxBuffer[3]<<8|V831_data.RxBuffer[4];
		Laji_y=V831_data.RxBuffer[5]<<8|V831_data.RxBuffer[6];
	  if (Laji == 1)
		{
			 sprintf (V831_Data_Buff,"page3.t4.txt=\"农夫水瓶\"");
			 HMI_SendString(V831_Data_Buff);
	     HMI_SendBit(0xff);
	     memset( V831_Data_Buff,0,sizeof(V831_Data_Buff));
//			 sprintf (V831_Data_Buff,"page3.t5.txt=\"%d\"",Distance[1]);
//			 HMI_SendString(V831_Data_Buff);
//	     HMI_SendBit(0xff);
//	     memset( V831_Data_Buff,0,sizeof(V831_Data_Buff));
		}
	  if (Laji == 2)
		{
			 sprintf (V831_Data_Buff,"page3.t4.txt=\"怡宝水瓶\"");
			 HMI_SendString(V831_Data_Buff);
	     HMI_SendBit(0xff);
	     memset( V831_Data_Buff,0,sizeof(V831_Data_Buff));
//			 sprintf (V831_Data_Buff,"page3.t5.txt=\"%d\"",Distance[1]);
//			 HMI_SendString(V831_Data_Buff);
//	     HMI_SendBit(0xff);
//	     memset( V831_Data_Buff,0,sizeof(V831_Data_Buff));
		}	
	  if (Laji == 3)
		{
			 sprintf (V831_Data_Buff,"page3.t4.txt=\"纸杯\"");
			 HMI_SendString(V831_Data_Buff);
	     HMI_SendBit(0xff);
	     memset( V831_Data_Buff,0,sizeof(V831_Data_Buff));
//			 sprintf (V831_Data_Buff,"page3.t5.txt=\"%d\"",Distance[1]);
//			 HMI_SendString(V831_Data_Buff);
//	     HMI_SendBit(0xff);
//	     memset( V831_Data_Buff,0,sizeof(V831_Data_Buff));
		}	
	  if (Laji == 4)
		{
			 sprintf (V831_Data_Buff,"page3.t4.txt=\"纸团\"");
			 HMI_SendString(V831_Data_Buff);
	     HMI_SendBit(0xff);
	     memset( V831_Data_Buff,0,sizeof(V831_Data_Buff));
//		 sprintf (V831_Data_Buff,"page3.t5.txt=\"%d\"",Distance[1]);
//		 HMI_SendString(V831_Data_Buff);
//		 HMI_SendBit(0xff);
//		 memset( V831_Data_Buff,0,sizeof(V831_Data_Buff));
		}		
		   sprintf (V831_Data_Buff,"page3.t5.txt=\"%d\"",Distance[1]);
			 HMI_SendString(V831_Data_Buff);
	     HMI_SendBit(0xff);
	     memset( V831_Data_Buff,0,sizeof(V831_Data_Buff));
}
/*·····巡线摄像头 串口接收数据帧初始化与数据处理·····*/
/**占据串口：UART_1
  *数据帧字长：RXBUFFER_LEN_OPENMV 8
	*数据帧头：0x55
**/
void User_USART_OPENMV_Init(User_USART_OPENMV *Data)
{
		for(uint16_t i=0; i < RXBUFFER_LEN_OPENMV; i++)	Data->RxBuffer[i] = 0;
		Data->frame_head = 0x55;
		Data->Rx_flag = 0;
		Data->Rx_len = 0;
}                                                 

void OPENMV_Process()
{
	   char  OPENMV_DataBuf[200];
		if(OPENMV_data.RxBuffer[0] != OPENMV_data.frame_head) return;  	
		line_x=OPENMV_data.RxBuffer[1]<<8|OPENMV_data.RxBuffer[2];
		line_y=OPENMV_data.RxBuffer[3]<<8|OPENMV_data.RxBuffer[4];
	  sprintf (OPENMV_DataBuf,"page2.t5.txt=\"%d\"",line_x);
	  HMI_SendString(OPENMV_DataBuf);
	  HMI_SendBit(0xff);
	  memset( OPENMV_DataBuf,0,sizeof(OPENMV_DataBuf));
	
	  sprintf (OPENMV_DataBuf,"page2.t6.txt=\"%d\"",line_y);
	  HMI_SendString(OPENMV_DataBuf);
	  HMI_SendBit(0xff);
	  memset( OPENMV_DataBuf,0,sizeof(OPENMV_DataBuf));
	
	  sprintf (OPENMV_DataBuf,"page2.t4.txt=\"成功·识别\"");
	  HMI_SendString(OPENMV_DataBuf);
	  HMI_SendBit(0xff);
	  memset( OPENMV_DataBuf,0,sizeof(OPENMV_DataBuf));	
}
