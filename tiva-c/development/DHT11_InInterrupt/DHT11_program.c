#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "TIMER0_interface.h"
#include "DHT11_interface.h"
#include "UART_interface.h"


void DHT11_vidInit(void)
{
	GPIO_vidSetPinDirection(DHT11_PORT,DHT11_PIN,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(DHT11_PORT,DHT11_PIN,GPIO_DEN_SET);
}

void DHT11_vidStart(void)
{
	GPIO_vidSetPinDirection(DHT11_PORT,DHT11_PIN,GPIO_OUTPUT);
	GPIO_vidSetPinValue(DHT11_PORT,DHT11_PIN,STD_LOW);
	TIMER0_vidDelayMicro(18000/TIMER0_MICRO_DIV);
	GPIO_vidSetPinValue(DHT11_PORT,DHT11_PIN,STD_HIGH);
	TIMER0_vidDelayMicro(20/TIMER0_MICRO_DIV);
	GPIO_vidSetPinDirection(DHT11_PORT,DHT11_PIN,GPIO_INPUT);
}

u8 DHT11_u8CheckResponse(void)
{
	u8 u8Response = 0;

	TIMER0_vidDelayMicro(50/TIMER0_MICRO_DIV);
	if (!GPIO_u8GetPinValue(DHT11_PORT,DHT11_PIN))
	{
		TIMER0_vidDelayMicro(84/TIMER0_MICRO_DIV);
		if (GPIO_u8GetPinValue(DHT11_PORT,DHT11_PIN))
		{
			u8Response = 1;
		}
		else
		{
			u8Response = 0;
		}
	}
			while(GPIO_u8GetPinValue(DHT11_PORT,DHT11_PIN));

	return u8Response;
}

u8 DHT11_u8ReadByte(void)
{
	u8 u8Byte;
	u8 u8BitIndex;
	for (u8BitIndex = 0; u8BitIndex < 8; u8BitIndex++)
	{
		while(!GPIO_u8GetPinValue(DHT11_PORT,DHT11_PIN));
		TIMER0_vidDelayMicro(32/TIMER0_MICRO_DIV);
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

u8 * DHT11_ptU8GetData(u8 * ptrU8DataArr)
{
	DHT11_vidStart();
	if (DHT11_u8CheckResponse() == 1)
	{
		ptrU8DataArr[0] = DHT11_u8ReadByte();
		ptrU8DataArr[1] = DHT11_u8ReadByte();
		ptrU8DataArr[2] = DHT11_u8ReadByte();
		ptrU8DataArr[3] = DHT11_u8ReadByte();
		/*Checksum*/
		ptrU8DataArr[4] = DHT11_u8ReadByte();
		
		/*Checking checksum*/
		if ((ptrU8DataArr[0] + ptrU8DataArr[1] + ptrU8DataArr[2] + ptrU8DataArr[3]) == ptrU8DataArr[4])
		{
			ptrU8DataArr[5] = DHT11_SUCCESS;
		}
		else
		{
			ptrU8DataArr[5] = DHT11_FAILURE;
		}
	}
}