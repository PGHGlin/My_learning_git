#include "ServoAction.h"
int servo1=170,servo2=190,servo3=100,servo4=60;
void Claw_Open()
{
	__HAL_TIM_SetCompare(&htim9,TIM_CHANNEL_2,180);
}
void Claw_Close()
{
	__HAL_TIM_SetCompare(&htim9,TIM_CHANNEL_2,230);
}
void Grab(int servovalue)
{
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,80);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,150);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_4,servovalue);
	__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,100);
	__HAL_TIM_SetCompare(&htim9,TIM_CHANNEL_1,60);

}

void ServoInit(void)
{
	__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,100);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,80);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,150);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_4,150);
	__HAL_TIM_SetCompare(&htim9,TIM_CHANNEL_1,100);
	Claw_Open();
}
void ServoUp(void)
{
	__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,100);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,80);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,150);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_4,150);
	__HAL_TIM_SetCompare(&htim9,TIM_CHANNEL_1,100);
	Claw_Close();
}
