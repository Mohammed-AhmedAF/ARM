#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "TIMER0_interface.h"
#include "SERVO_interface.h"

void SERVO_vidInit(const ServoConfig_t * conf)
{
	GPIO_vidSetPinDirection(conf->u8SignalPort,conf->u8SignalPin,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(conf->u8SignalPort,conf->u8SignalPin,GPIO_DEN_SET);
}

void SERVO_0_Degree(const ServoConfig_t * conf)
{
   int i=0;  	 
	for(i=0; i<50; i++) 
	{
	  /* Given 10us trigger pulse */
		GPIO_vidSetPinValue(conf->u8SignalPort,conf->u8SignalPin,1); /* make control  pin high */
	  TIMER0_viDelayMirco(600); /*0.6ms seconds delay */
		GPIO_vidSetPinValue(conf->u8SignalPort,conf->u8SignalPin,0); /* make control  pin high */
	  TIMER0_viDelayMirco(19400); /*1.94ms seconds delay */
  }
}

/* This function generate a 7% duty cycle from 20ms PWM signal or 50Hz*/
void SERVO_90_Degree(const ServoConfig_t * conf)
{
   int i=0; 
	 for(i=0; i<50; i++) 
    {	
		/* Given 10us trigger pulse */
		/* make control  pin high */
		GPIO_vidSetPinValue(conf->u8SignalPort,conf->u8SignalPin,1); 
		TIMER0_viDelayMirco(1400); /*1.4ms seconds delay */
		/* make control  pin high */
		GPIO_vidSetPinValue(conf->u8SignalPort,conf->u8SignalPin,0);
	  TIMER0_viDelayMirco(18600); /*1.86ms seconds delay */
		}
}

/* This function generate a 12% duty cycle from 20ms PWM signal or 50Hz*/
void SERVO_180_Degree(const ServoConfig_t * conf)
{
   	int i=0; 
	  for(i=0; i<50; i++) 
    {
	  /* Given 10us trigger pulse */			
		/* make control  pin high */
		GPIO_vidSetPinValue(conf->u8SignalPort,conf->u8SignalPin,1); 
	  /*2.4ms seconds delay */
		TIMER0_viDelayMirco(2400); 
	  /* make trigger  pin high */
		GPIO_vidSetPinValue(conf->u8SignalPort,conf->u8SignalPin,0);
		TIMER0_viDelayMirco(17600); /*1.76ms seconds delay */
		}
}