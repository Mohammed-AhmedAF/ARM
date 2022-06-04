#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "TM1637_config.h"
#include "TM1637_interface.h"
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"

const u8 segmentMap[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, // 8-9, A-F
    0x00
};

void TM1637_vidInit(void)
{
	/*DIO pin configuration*/
	GPIO_vidSetPinDirection(TM1637_DIO_PORT,TM1637_DIO_PIN,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(TM1637_DIO_PORT,TM1637_DIO_PIN,GPIO_DEN_SET);
	
	/*CLK pin configuration*/
	GPIO_vidSetPinDirection(TM1637_CLK_PORT,TM1637_CLK_PIN,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(TM1637_CLK_PORT,TM1637_CLK_PIN,GPIO_DEN_SET);
	
	TM1637_vidSetBrightness(8);
}

static void TM1637_vidStart(void)
{
	TM1637_vidSetClkHigh();
	TM1637_vidSetDIOHigh();
	TM1637_vidDelay(20);
	TM1637_vidSetDIOLow();
}

static void TM1637_vidStop(void)
{
	TM1637_vidSetClkLow();
	TM1637_vidDelay(20);
	TM1637_vidSetDIOLow();
	TM1637_vidDelay(20);
	TM1637_vidSetClkHigh();
	TM1637_vidDelay(20);
	TM1637_vidSetDIOHigh();
}

static void TM1637_vidSetClkHigh(void)
{
	GPIO_vidSetPinValue(TM1637_CLK_PORT,TM1637_CLK_PIN,STD_HIGH);
}

static void TM1637_vidSetClkLow(void)
{
	GPIO_vidSetPinValue(TM1637_CLK_PORT,TM1637_CLK_PIN,STD_LOW);
}

static void TM1637_vidSetDIOHigh(void)
{
	GPIO_vidSetPinValue(TM1637_DIO_PORT,TM1637_DIO_PIN,STD_HIGH);
}

static void TM1637_vidSetDIOLow(void)
{
	GPIO_vidSetPinValue(TM1637_DIO_PORT,TM1637_DIO_PIN,STD_LOW);
}

static u8 TM1637_u8ReadResult(void)
{
	TM1637_vidSetClkLow();
	TM1637_vidDelay(50);
	
	TM1637_vidSetClkHigh();
	TM1637_vidDelay(20);
	TM1637_vidSetClkLow();

	return 0x15;
}

static void TM1637_vidWriteByte(u8 u8Byte)
{
 for (u8 i = 0; i < 8; ++i)
	{
		TM1637_vidSetClkLow();
		if (u8Byte & 0x01)
		{
			TM1637_vidSetDIOHigh();
		}
		else 
		{
			TM1637_vidSetDIOLow();
		}
	
		TM1637_vidDelay(30);
		
		u8Byte >>= 1;
		TM1637_vidSetClkHigh();
		TM1637_vidDelay(30);
	}
}


static void TM1637_vidDelay(u8 u8DelayVal)
{
	SysCtlDelay(u8DelayVal * (SysCtlClockGet() / 3 / 1000000));
}

void TM1637_vidDelayM(u32 u32DelayVal)
{
	SysCtlDelay(u32DelayVal * (SysCtlClockGet() / 3 / 1000));	
}

void TM1637_vidDisplayChar(u8 u8CharArr)
{
	u8 digitArr[4];
	
	digitArr[0] = segmentMap[10];
	digitArr[1] = segmentMap[10];
	digitArr[2] = segmentMap[10];
	digitArr[3] = segmentMap[15];

	
	TM1637_vidStart();
	TM1637_vidWriteByte(0x40);
	TM1637_u8ReadResult();
	TM1637_vidStop();
	
	
	TM1637_vidStart();
	TM1637_vidWriteByte(0xC0);
	TM1637_u8ReadResult();
	
	for (u8 i = 0; i < 4; i++)
	{
		TM1637_vidWriteByte(digitArr[3-i]);
		TM1637_u8ReadResult();
	}
	
	TM1637_vidStop();
}

void TM1637_vidDisplayDecimal(u32 u32Val, u8 u8DisplaySeparator)
{
	u8 digitArr[4];
	for (u8 u8DigitIndex = 0; u8DigitIndex < 4; u8DigitIndex++)
	{
		digitArr[u8DigitIndex] = segmentMap[u32Val%10];
		if (u8DigitIndex == 2 && u8DisplaySeparator)
		{
			digitArr[u8DigitIndex] |= 1<<7;
		}
		u32Val /= 10;
	}
	


	TM1637_vidStart();
	TM1637_vidWriteByte(0x40);
	TM1637_u8ReadResult();
	TM1637_vidStop();
	
	
	TM1637_vidStart();
	TM1637_vidWriteByte(0xC0);
	TM1637_u8ReadResult();
	
	for (u8 i = 0; i < 4; i++)
	{
		TM1637_vidWriteByte(digitArr[3-i]);
		TM1637_u8ReadResult();
	}
	
	TM1637_vidStop();
	
}

void TM1637_vidSetBrightness(u8 u8BrightnessLevel)
{

 TM1637_vidStart();
 TM1637_vidWriteByte(0x87+u8BrightnessLevel);
 TM1637_u8ReadResult();
 TM1637_vidStop();



}