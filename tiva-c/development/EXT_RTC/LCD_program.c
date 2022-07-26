#include "Macros.h"
#include "STD_TYPES.h"
#include "I2C_interface.h"
#include "LCD_interface.h"
#include "TIMER0_interface.h"

#define SLAVE_ADDRESS_LCD 0x27

void LCD_vidInit(void)
{
	TIMER0_vidDelayMilli(50);
	LCD_vidSendCommand(0x03);
	TIMER0_vidDelayMilli(5);
	LCD_vidSendCommand(0x03);
	TIMER0_vidDelayMilli(1);
	LCD_vidSendCommand(0x03);
	TIMER0_vidDelayMilli(10);

	LCD_vidSendCommand(0x02);
	TIMER0_vidDelayMilli(10);

	
	
	/*Display initialization*/
	LCD_vidSendCommand(0x28);
	TIMER0_vidDelayMilli(1);
	LCD_vidSendCommand(0x08);
	TIMER0_vidDelayMilli(1);
	LCD_vidSendCommand(0x01);
	TIMER0_vidDelayMilli(1);
	TIMER0_vidDelayMilli(1);
	LCD_vidSendCommand(0x06);
	TIMER0_vidDelayMilli(1);
	LCD_vidSendCommand(0x0C);
}

void LCD_vidSendCommand(u8 u8Command)
{
	u8 data_u, data_l;
	u8 data_t[4];
	data_u = (u8Command&0xf0);
	data_l = ((u8Command<<4)&0xf0);
	data_t[0] = data_u|0x0C;
	data_t[1] = data_u|0x08;
	data_t[2] = data_l|0x0C;
	data_t[3] = data_l|0x08;
	I2C1_u32SendMultipleBytes(SLAVE_ADDRESS_LCD,(u8*)data_t,4);
	
}

void LCD_vidClearScreen(void)
{
	LCD_vidSendCommand(0x01);
}

void LCD_vidWriteCharacter(u8 u8Character)
{
	u8 data_u, data_l;
	u8 data_t[4];
	data_u = (u8Character&0xf0);
	data_l = ((u8Character<<4)&0xf0);
	
	data_t[0] = data_u|0x0D; //en=1,rs=1
	data_t[1] = data_u|0x09; //en=0,rs=1
	data_t[2] = data_l|0x0D; //en=1,rs=1
	data_t[3] = data_l|0x09; //en=0,rs=1
	I2C1_u32SendMultipleBytes(SLAVE_ADDRESS_LCD,data_t,4);
	
}

void LCD_vidSetCursor(u8 u8xPos, u8 u8yPos)
{
	u8 i = 0;
	switch(u8yPos)
	{
		case 0:
			LCD_vidSendCommand(0x80);
			break;
		case 1:
			LCD_vidSendCommand(0xC0);
			break;
		case 2:
			LCD_vidSendCommand(0x94);
			break;
		case 3:
			LCD_vidSendCommand(0xD4);
			break;
	}
	
	for (i = 0; i < u8xPos; i++)
	{
		LCD_vidSendCommand(0x14);
	}
}

void delayMilli(u32 u32Milli)
{
	u32 milliCount;
	u32 j;
	for (milliCount = 0; milliCount < u32Milli; milliCount++)
	{
		for (j = 0; j < 3180; j++)
		{
		
		}
	}
}