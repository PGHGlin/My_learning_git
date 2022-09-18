#include "ServoAction.h"
int e=80,b=150,c=150,d=200,m=100;

void Claw_Open(void)
{
	__HAL_TIM_SetCompare(&htim9,TIM_CHANNEL_2,200);
}
void Claw_Close(void)
{
	__HAL_TIM_SetCompare(&htim9,TIM_CHANNEL_2,230);
}
void GrabBottle1(void)
{
	__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,100);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,170);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,150);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_4,190);
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

