#ifndef _SERVO_INTERFACE_H
#define _SERVO_INTERFACE_H

typedef struct
{
	u8 u8SignalPort;
	u8 u8SignalPin;
}ServoConfig_t;


void SERVO_vidInit(const ServoConfig_t * conf);
void SERVO_0_Degree(const ServoConfig_t * conf);
void SERVO_90_Degree(const ServoConfig_t * conf);
void SERVO_180_Degree(const ServoConfig_t * conf);
#endif