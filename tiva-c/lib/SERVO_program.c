#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SERVO_interface.h"

/*Pointer to function micro delay*/
static void (*ptrFunMicroDelay) (u32);

void SERVO_vidInit(const ServoConfig_t * conf)
{
	GPIO_vidSetPinDirection(conf->u8SignalPort,conf->u8SignalPin,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(conf->u8SignalPort,conf->u8SignalPin,GPIO_DEN_SET);
	
	/*Setting micro delay timer function*/
	SERVO_vidSetDelayTimerFunc(conf->ptFMicroDelay);
}

void SERVO_vidSetDelayTimerFunc(void (*ptrF) (u32))
{
	ptrFunMicroDelay = ptrF;
}

void SERVO_0_Degree(const ServoConfig_t * conf)
{
  u8 u8Cycle=0;  	 
	for(u8Cycle=0; u8Cycle < 50; u8Cycle++) 
	{
	  /* Given 10us trigger pulse */
		/*Control pin high */
		GPIO_vidSetPinValue(conf->u8SignalPort,conf->u8SignalPin,1);
	  ptrFunMicroDelay(600); /*0.6ms seconds delay */
		/*Control pin low */
		GPIO_vidSetPinValue(conf->u8SignalPort,conf->u8SignalPin,0); 
	  ptrFunMicroDelay(19400); /*1.94ms seconds delay */
  }
}

/* This function generates a 7% duty cycle from 20ms PWM signal or 50Hz*/
void SERVO_90_Degree(const ServoConfig_t * conf)
{
   u8 u8Cycle = 0; 
	 for(u8Cycle = 0; u8Cycle < 50; u8Cycle++) 
   {	
		/*Given 10us trigger pulse */
		/*Control pin high */
		GPIO_vidSetPinValue(conf->u8SignalPort,conf->u8SignalPin,1); 
		ptrFunMicroDelay(1400); /*1.4ms seconds delay */
		/*Control pin high */
		GPIO_vidSetPinValue(conf->u8SignalPort,conf->u8SignalPin,0);
	  ptrFunMicroDelay(18600); /*1.86ms seconds delay */
	}
}

/* This function generates a 12% duty cycle from 20ms PWM signal or 50Hz*/
void SERVO_180_Degree(const ServoConfig_t * conf)
{
   	u8 u8Cycle = 0; 
	  for(u8Cycle = 0; u8Cycle < 50; u8Cycle++) 
    {
			/*Given 10us trigger pulse */			
			/*Control pin high */
			GPIO_vidSetPinValue(conf->u8SignalPort,conf->u8SignalPin,1); 
			/*2.4ms seconds delay*/
			ptrFunMicroDelay(2400); 
			/*Trigger pin high*/
			GPIO_vidSetPinValue(conf->u8SignalPort,conf->u8SignalPin,0);
			ptrFunMicroDelay(17600); /*1.76ms seconds delay */
		}
}