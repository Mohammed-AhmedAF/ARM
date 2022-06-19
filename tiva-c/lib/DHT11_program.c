#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "TIMER0_private.h"
#include "TIMER0_interface.h"
#include "DHT11_interface.h"
#include "DHT_config.h"

void DHT11_vidInit(void)
{
	GPIO_vidSetPinDirection(DHT11_PORT,DHT11_PIN,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(DHT11_PORT,DHT11_PIN,GPIO_DEN_SET);
}

void DHT11_vidStart(void)
{
	GPIO_vidSetPinDirection(DHT11_PORT,DHT11_PIN,GPIO_OUTPUT);
	GPIO_vidSetPinValue(DHT11_PORT,DHT11_PIN,STD_LOW);
	#ifdef _DHT_DHT11
	TIMER0_vidDelayMilli(18);
	#elif _DHT_DHT22
	TIMER0_vidDelayMilli(12);
	#endif
	GPIO_vidSetPinValue(DHT11_PORT,DHT11_PIN,STD_HIGH);
	TIMER0_viDelayMirco(20);
	GPIO_vidSetPinDirection(DHT11_PORT,DHT11_PIN,GPIO_INPUT);
}

u8 DHT11_u8CheckResponse(void)
{
	u8 u8Response = 0;
	TIMER0_viDelayMirco(40);
	if (!GPIO_u8GetPinValue(DHT11_PORT,DHT11_PIN))
	{
		TIMER0_viDelayMirco(80);
		if (GPIO_u8GetPinValue(DHT11_PORT,DHT11_PIN))
		{
			u8Response = DHT11_RESPONSE_GOOD;
		}
		else
		{
			u8Response = DHT11_RESPONSE_BAD;
		}
	}
	TIMER0_viDelayMirco(60);
	return u8Response;
}

u8 DHT11_u8ReadByte(void)
{
	u8 u8Byte;
	u8 u8BitIndex;
	/*Have to put this diable timer macro in order to prevent the program from hanging*/
	TIMER0_DISABLE_TIMER();
	for (u8BitIndex = 0; u8BitIndex < 8; u8BitIndex++)
	{
		while(!GPIO_u8GetPinValue(DHT11_PORT,DHT11_PIN));
		TIMER0_DISABLE_TIMER();
		TIMER0_viDelayMirco(10);
		TIMER0_viDelayMirco(10);
		TIMER0_viDelayMirco(10);
		TIMER0_viDelayMirco(10);
		if (!GPIO_u8GetPinValue(DHT11_PORT,DHT11_PIN))
		{
			u8Byte &= ~(1<<(7-u8BitIndex));
		}
		else
		{
			u8Byte |= (1<<(7-u8BitIndex));
		}
		while(GPIO_u8GetPinValue(DHT11_PORT,DHT11_PIN));
	}
	
	return u8Byte;
}