#include "ShakeMotor.h"
#include "BF_type.h"
#include "GPIO.h"
#include "delay.h"
#include "Thread.h"

u8 MotorRun_Flag;
u8 GetMPU6050Flag;

void ShakeMotor_Init(void)
{	
	GPIOx_Cfg(MOTOR_PORT, MOTOR_PIN, OUT_PP_2M);
	GPIOx_Rst(MOTOR_PORT, MOTOR_PIN);
}
//带延时函数的马达震动
void ShakeMotor_RunAndDelay(void)
{
	GPIOx_Set(MOTOR_PORT, MOTOR_PIN);
	delay_ms(100);
	GPIOx_Rst(MOTOR_PORT, MOTOR_PIN);
	GetMPU6050Flag=0;
}
//不带延时函数的 马达震动
void ShakeMotor_Run(void)
{
	static u8 run_count;
	static u8 stop_count;
	if(MotorRun_Flag==1)
	{
		MotorRun_Flag = 0;
		run_count = 2;
		stop_count= 3;
	}
	else if(MotorRun_Flag==2)
	{
		MotorRun_Flag = 0;
		run_count = 6;
		stop_count= 3;
	}
	if(run_count)
	{
		run_count--;
		GPIOx_Set(MOTOR_PORT, MOTOR_PIN);
	}
	else if(stop_count)
	{
		stop_count--;
		GPIOx_Rst(MOTOR_PORT, MOTOR_PIN);
		if(stop_count==0) GetMPU6050Flag=0;
	}
}
void ShakeMotor_OFF(void)
{
	GPIOx_Rst(MOTOR_PORT, MOTOR_PIN);
	GetMPU6050Flag=0;
}

void ShakeMotor_RunOnce(void)
{
	GPIOx_Set(MOTOR_PORT, MOTOR_PIN);
	Thread_Login(ONCEDELAY, 0, 70, &ShakeMotor_OFF);
}

