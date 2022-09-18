#include "encoder.h"
#include "main.h"
/*
    @brief: 获得左右轮速度
    @param：xxxPluse 编码器软件4倍频，编码器硬件线数13ppr，故除以52，根据v = 2*pi*n*r得速度
*/
int APluse;
int BPluse;
int CPluse;
int DPluse;



short Get_ASpeed(void)
{
   APluse =(short) (__HAL_TIM_GetCounter(&htim2));
	__HAL_TIM_SetCounter (&htim2,0);
	return APluse;
}

short Get_BSpeed(void)
{
   BPluse =(short) (__HAL_TIM_GetCounter(&htim3));
	__HAL_TIM_SetCounter (&htim3,0);
	return BPluse;
}

short Get_CSpeed(void)
{
   CPluse =(short) (__HAL_TIM_GetCounter(&htim4));
	__HAL_TIM_SetCounter (&htim4,0);
	return CPluse;
}

short Get_DSpeed(void)
{
   DPluse =(short) (__HAL_TIM_GetCounter(&htim1));
	__HAL_TIM_SetCounter (&htim1,0);
	return DPluse;
}


