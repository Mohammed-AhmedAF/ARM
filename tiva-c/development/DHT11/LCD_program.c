#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "LCD_interface.h"

/*LCD driver in 4-bit mode*/

void LCD_vidInit(void)
{
	/*GPIO configuration*/
	GPIO_vidSetPinDirection(LCD_PORT_D4,LCD_PIN_D4,GPIO_OUTPUT);
	GPIO_vidSetPinDirection(LCD_PORT_D5,LCD_PIN_D5,GPIO_OUTPUT);
	GPIO_vidSetPinDirection(LCD_PORT_D6,LCD_PIN_D6,GPIO_OUTPUT);
	GPIO_vidSetPinDirection(LCD_PORT_D7,LCD_PIN_D7,GPIO_OUTPUT);

	GPIO_vidSetPinDigEnable(LCD_PORT_D4,LCD_PIN_D4,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(LCD_PORT_D5,LCD_PIN_D5,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(LCD_PORT_D6,LCD_PIN_D6,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(LCD_PORT_D7,LCD_PIN_D7,GPIO_DEN_SET);

	
	GPIO_vidSetPinDirection(LCD_PORT_RS,LCD_PIN_RS,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(LCD_PORT_RS,LCD_PIN_RS,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(LCD_PORT_RW,LCD_PIN_RW,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(LCD_PORT_RW,LCD_PIN_RW,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(LCD_PORT_EN,LCD_PIN_EN,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(LCD_PORT_EN,LCD_PIN_EN,GPIO_DEN_SET);
	
	LCD_vidSendCommand(0x02);
	LCD_vidSendCommand(0x28);
	LCD_vidSendCommand(LCD_CLEAR_SCREEN); /*Clear screen*/
	LCD_vidSendCommand(LCD_RETURN_HOME); /*Move to home*/
	LCD_vidSendCommand(LCD_SET_ENTRY_MODE|LCD_MOVE_CURSOR_RIGHT); /*Set entry mode*/
	LCD_vidSendCommand(LCD_DISPLAY_ON); /*Display On/Off control*/
	delay_milli(20);

}

void LCD_vidSendCommand(u8 u8Command)
{
	GPIO_vidSetPinValue(LCD_PORT_D4,LCD_PIN_D4,GET_BIT(u8Command,4));
	GPIO_vidSetPinValue(LCD_PORT_D5,LCD_PIN_D5,GET_BIT(u8Command,5));
	GPIO_vidSetPinValue(LCD_PORT_D6,LCD_PIN_D6,GET_BIT(u8Command,6));
	GPIO_vidSetPinValue(LCD_PORT_D7,LCD_PIN_D7,GET_BIT(u8Command,7));

	/*RS=0*/
	GPIO_vidSetPinValue(LCD_PORT_RS,LCD_PIN_RS,STD_LOW);
	
	/*Sending enable signal*/
	GPIO_vidSetPinValue(LCD_PORT_EN,LCD_PIN_EN,STD_HIGH);
	delay_micro(1);
	GPIO_vidSetPinValue(LCD_PORT_EN,LCD_PIN_EN,STD_LOW);
	delay_micro(200);
	
	GPIO_vidSetPinValue(LCD_PORT_D4,LCD_PIN_D4,GET_BIT(u8Command,0));
	GPIO_vidSetPinValue(LCD_PORT_D5,LCD_PIN_D5,GET_BIT(u8Command,1));
	GPIO_vidSetPinValue(LCD_PORT_D6,LCD_PIN_D6,GET_BIT(u8Command,2));
	GPIO_vidSetPinValue(LCD_PORT_D7,LCD_PIN_D7,GET_BIT(u8Command,3));

	GPIO_vidSetPinValue(LCD_PORT_EN,LCD_PIN_EN,STD_HIGH);
	delay_micro(1);
	GPIO_vidSetPinValue(LCD_PORT_EN,LCD_PIN_EN,STD_LOW);
	delay_milli(5);
}

void LCD_vidWriteCharacter(u8 u8Char)
{
	GPIO_vidSetPinValue(LCD_PORT_D4,LCD_PIN_D4,GET_BIT(u8Char,4));
	GPIO_vidSetPinValue(LCD_PORT_D5,LCD_PIN_D5,GET_BIT(u8Char,5));
	GPIO_vidSetPinValue(LCD_PORT_D6,LCD_PIN_D6,GET_BIT(u8Char,6));
	GPIO_vidSetPinValue(LCD_PORT_D7,LCD_PIN_D7,GET_BIT(u8Char,7));

	/*RS=1*/
	GPIO_vidSetPinValue(LCD_PORT_RS,LCD_PIN_RS,STD_HIGH);
	
	/*Sending enable signal*/
	GPIO_vidSetPinValue(LCD_PORT_EN,LCD_PIN_EN,STD_HIGH);
	delay_micro(1);
	GPIO_vidSetPinValue(LCD_PORT_EN,LCD_PIN_EN,STD_LOW);
	delay_micro(200);
	
	GPIO_vidSetPinValue(LCD_PORT_D4,LCD_PIN_D4,GET_BIT(u8Char,0));
	GPIO_vidSetPinValue(LCD_PORT_D5,LCD_PIN_D5,GET_BIT(u8Char,1));
	GPIO_vidSetPinValue(LCD_PORT_D6,LCD_PIN_D6,GET_BIT(u8Char,2));
	GPIO_vidSetPinValue(LCD_PORT_D7,LCD_PIN_D7,GET_BIT(u8Char,3));

	GPIO_vidSetPinValue(LCD_PORT_EN,LCD_PIN_EN,STD_HIGH);
	delay_micro(1);
	GPIO_vidSetPinValue(LCD_PORT_EN,LCD_PIN_EN,STD_LOW);
	delay_milli(5);
}

void LCD_vidWriteNumber(u16 u16NumberCpy) {
	if(u16NumberCpy < 10) {
		LCD_vidWriteCharacter('0');
		LCD_vidWriteCharacter(u16NumberCpy+'0');
	}
	else {
		if (u16NumberCpy < 100) {
			LCD_vidWriteCharacter(u16NumberCpy/10+'0');
			LCD_vidWriteCharacter(u16NumberCpy%10+'0');
		}
		else if (u16NumberCpy < 1000) {
			LCD_vidWriteCharacter((u16NumberCpy/100)+'0');
			LCD_vidWriteCharacter((u16NumberCpy%100)/10+'0');
			LCD_vidWriteCharacter((u16NumberCpy%100)%10+'0');
		}
		else if (u16NumberCpy < 10000)
		{
			LCD_vidWriteCharacter((u16NumberCpy/1000)+'0');
			LCD_vidWriteCharacter((u16NumberCpy%1000)/100+'0');
			LCD_vidWriteCharacter((u16NumberCpy%100)/10+'0');
			LCD_vidWriteCharacter((u16NumberCpy%100)%10+'0');
		}
	}
}

void LCD_vidWriteString(s8 * s8String) {	
	do {
		LCD_vidWriteCharacter(*s8String);
		(s8String++);
	}while(*s8String != '\0');
}


void delay_micro(int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < 3; j++) {	
		}
	}
}

void  delay_milli(int n) {
	int i, j;
	for (i = 0;  i < n; i++) {
		for (j = 0; j < 3180; j++) {
		}
	}
}