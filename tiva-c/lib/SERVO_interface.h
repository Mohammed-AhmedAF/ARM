#ifndef _SERVO_INTERFACE_H
#define _SERVO_INTERFACE_H

typedef struct
{
	u8 u8SignalPort;
	u8 u8SignalPin;
	void (*ptFMicroDelay) (u32);
}ServoConfig_t;


void SERVO_vidInit(const ServoConfig_t * conf);
void SERVO_0_Degree(const ServoConfig_t * conf);
void SERVO_90_Degree(const ServoConfig_t * conf);
void SERVO_180_Degree(const ServoConfig_t * conf);
void SERVO_vidSetDelayTimerFunc(void (*ptrF) (u32));
#endif