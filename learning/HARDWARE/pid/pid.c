#include "pid.h"
#include "encoder.h"

float SpeedNow =0;
float SpeedError =0;
int speed1,speed2,speed3,speed4; 
short Rspeed1,Rspeed2,Rspeed3,Rspeed4;
int Final_A,Final_B,Final_C,Final_D;

	

struct PID wheel1={
									-630,
									-0.13,
									0
									};
struct PID wheel2={
									-630,
									-0.13,
									0
									};
struct PID wheel3={
									-630,
									-0.13,
									0
									};
struct PID wheel4={
									-630,
									-0.13,
									0
									};
									


void Speedpid_init(SPEED_PID* p)
{
    p->speed_kp = 0;
    p->speed_ki= 0;
    p->speed_kd = 0;
}
void Anglepid_init(ANGLE_PID* p)
{
    p->angle_kp = 0;
    p->angle_ki = 0;
    p->angle_kd = 0;
}
void Positionpid_init(POSITION_PID* p)
{
    p->position_kp = 0;
    p->position_ki = 0;
    p->position_kd = 0;
}
int speed_pid(struct PID *p,short Real,int Expect )
{
	static int output,output_p,output_i,output_d,error,sum,error_filter,error_filter_last,error_last;
  float index=0.8;
	error=Real-Expect;
	error_filter=(1-index)*error+index*error_filter_last;
	error_filter_last=error_filter;
	error_last=error;
	sum+=error_filter;
	sum=sum>10000?10000:(sum<(-10000)?(-10000):sum);
	output_p=p->speed_kp*error;
	output_i=p->speed_ki*sum;
	output_d=p->speed_kd*(error-error_last);
	output=output_p+output_i+output_d;
	return output;

}


/*
麦克纳姆轮速度解算：此计算为O型安装																		
		运动分为三个方向																								  
		x轴、y轴、几何中心自转


		 ---  Vw1=-Vtx										 ---  Vw1= Vty								  	   ---  Vw1=+w(a+b)									
	   |																	|															      |
	   ---  Vw2=+Vtx										 ---  Vw2= Vty								       ---  Vw2=-w(a+b)
 << |												     << |														     << |
		 ---  Vw3=-Vtx										 ---  Vw3= Vty									     ---  Vw3=-w(a+b)							 
		|																	|																    |
		 ---  Vw4=+Vtx										 ---  Vw4= Vty									     ---  Vw4=+w(a+b)

 
									//1			 \\2									      y	    ^ 
									|																|
								b	|																|_____>
									|----·																x
										 a	
									\\4			  //3

*/



void Mcnamu(int Target_X,int Target_Y,int w)
{

		
	
	speed1= Target_X+Target_Y-w;
	speed2=-Target_X+Target_Y+w;
	speed3=-Target_X+Target_Y-w;
	speed4= Target_X+Target_Y+w;//求出四个轮子的期望速度
	
	if(speed1>0)    	{AIN1_0(); AIN2_1();}
	else if(speed1<0)	{AIN1_1(); AIN2_0();}
	if(speed2>0)    	{BIN1_0(); BIN2_1();}
	else if(speed2<0)	{BIN1_1(); BIN2_0();}
	if(speed3>0)    	{CIN1_0(); CIN2_1();}
	else if(speed3<0)	{CIN1_1(); CIN2_0();}
	if(speed4>0)    	{DIN1_0(); DIN2_1();}
	else if(speed4<0)	{DIN1_1(); DIN2_0();}	
	
	Rspeed1=Get_BSpeed();
	Rspeed2=-Get_ASpeed();
	Rspeed3=Get_DSpeed();
	Rspeed4=Get_CSpeed();//获取当前轮子的实际转速
	
	Final_A=speed_pid(&wheel1,Rspeed1,speed1);
	Final_B=speed_pid(&wheel2,Rspeed2,speed2);
	Final_C=speed_pid(&wheel3,Rspeed3,speed3);
	Final_D=speed_pid(&wheel4,Rspeed4,speed4);//速度闭环控制
	
	Final_A=Final_A<0?(-Final_A):Final_A;
	Final_B=Final_B<0?(-Final_B):Final_B;
	Final_C=Final_C<0?(-Final_C):Final_C;
	Final_D=Final_D<0?(-Final_D):Final_D;//对速度取绝对值
	
	Final_A=Final_A>8000?8000:Final_A;
	Final_B=Final_B>8000?8000:Final_B;
	Final_C=Final_C>8000?8000:Final_C;
	Final_D=Final_D>8000?8000:Final_D;
	
	__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,Final_A);
	__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,Final_B);
	__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,Final_C);
	__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_4,Final_D);//赋值
	
}

