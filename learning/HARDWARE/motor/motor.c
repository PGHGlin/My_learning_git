#include "motor.h"



void motor_stop(void)
{
     AIN1_0();
     AIN2_0();
     BIN1_0();
     BIN2_0();
     CIN1_0();
     CIN2_0();
     DIN1_0();
     DIN2_0();
}


