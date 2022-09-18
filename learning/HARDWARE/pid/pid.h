#ifndef _PID_H_
#define _PID_H_



#include "tim.h"
#include "motor.h"
#include "encoder.h"
#include "main.h"


	typedef struct PID
	{
			float speed_kp;
			float speed_ki;
			float speed_kd;
	}SPEED_PID;

typedef struct ANGLE_PID
{
    float angle_kp;
    float angle_ki;
    float angle_kd;
}ANGLE_PID;

typedef struct POSITION_PID
{
    float position_kp;
    float position_ki;
    float position_kd;
}POSITION_PID;




extern ANGLE_PID angle_pid;
extern POSITION_PID position_pid;

void Mcnamu(int Target_X,int Target_Y,int ω);
void Angle_pid(void);
void Position_pid(void);
void Speedpid_init(SPEED_PID* p);
void Anglepid_init(ANGLE_PID* p);
void Positionpid_init(POSITION_PID*p);
int speed_pid(struct PID *p,short Real,int Expect );



#endif
