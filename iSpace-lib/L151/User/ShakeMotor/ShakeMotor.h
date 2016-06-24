#ifndef _SHAKE_MOTOR_H_
#define _SHAKE_MOTOR_H_

#include "BF_type.h"

#define MOTOR_PORT GPIO_B
#define MOTOR_PIN  pin_9


extern u8 MotorRun_Flag;
extern u8 GetMPU6050Flag;

void ShakeMotor_Init(void);
void ShakeMotor_Run(void);
void ShakeMotor_RunAndDelay(void);
void ShakeMotor_RunOnce(void);

#endif
