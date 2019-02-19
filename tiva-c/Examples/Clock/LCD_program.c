// File: LCD_prog.c
// Author: Mohammed Ahmed Abd Al-Fattah
//

#include "Std_Types.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "LCD_interface.h"



void LCD_vidInit(void) {
	GPIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D0,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(LCD_DATA_PORT,LCD_D0,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D1,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(LCD_DATA_PORT,LCD_D1,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(LCD_DATA_PORT,LCD_D2,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D3,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(LCD_DATA_PORT,LCD_D3,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D4,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(LCD_DATA_PORT,LCD_D4,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D5,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(LCD_DATA_PORT,LCD_D5,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D6,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(LCD_DATA_PORT,LCD_D6,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D7,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(LCD_DATA_PORT,LCD_D7,GPIO_DEN_SET);


	GPIO_vidSetPinDirection(LCD_CTRL_PORT,LCD_E,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(LCD_CTRL_PORT,LCD_E,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(LCD_CTRL_PORT,LCD_RS,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(LCD_CTRL_PORT,LCD_RS,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(LCD_CTRL_PORT,LCD_RW,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(LCD_CTRL_PORT,LCD_RW,GPIO_DEN_SET);
	
	LCD_vidSendCommand(LCD_CLEAR_SCREEN); 
	LCD_vidSendCommand(LCD_RETURN_HOME); 
	LCD_vidSendCommand(0b00000110); 
	LCD_vidSendCommand(0b00001100); 
	LCD_vidSendCommand(0b00111000);

}

void LCD_vidSendCommand(u8 commandCpy) {
	GPIO_vidSetPinValue(LCD_CTRL_PORT,LCD_RS,STD_LOW);
	GPIO_vidSetPinValue(LCD_CTRL_PORT,LCD_RW,STD_LOW);

	GPIO_vidSetPinValue(LCD_DATA_PORT,LCD_D0,GET_BIT(commandCpy,0));
	GPIO_vidSetPinValue(LCD_DATA_PORT,LCD_D1,GET_BIT(commandCpy,1));
	GPIO_vidSetPinValue(LCD_DATA_PORT,LCD_D2,GET_BIT(commandCpy,2));
	GPIO_vidSetPinValue(LCD_DATA_PORT,LCD_D3,GET_BIT(commandCpy,3));
	GPIO_vidSetPinValue(LCD_DATA_PORT,LCD_D4,GET_BIT(commandCpy,4));
	GPIO_vidSetPinValue(LCD_DATA_PORT,LCD_D5,GET_BIT(commandCpy,5));
	GPIO_vidSetPinValue(LCD_DATA_PORT,LCD_D6,GET_BIT(commandCpy,6));
	GPIO_vidSetPinValue(LCD_DATA_PORT,LCD_D7,GET_BIT(commandCpy,7));

	GPIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_HIGH);
	delay_milli(2);
	GPIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_LOW);
	delay_milli(2);
	GPIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_HIGH);
	delay_milli(2);
}

void LCD_vidWriteCharacter(u8 charCpy) {
	GPIO_vidSetPinValue(LCD_CTRL_PORT,LCD_RS,STD_HIGH);
	GPIO_vidSetPinValue(LCD_CTRL_PORT,LCD_RW,STD_LOW);

	GPIO_vidSetPinValue(LCD_DATA_PORT,LCD_D0,GET_BIT(charCpy,0));
	GPIO_vidSetPinValue(LCD_DATA_PORT,LCD_D1,GET_BIT(charCpy,1));
	GPIO_vidSetPinValue(LCD_DATA_PORT,LCD_D2,GET_BIT(charCpy,2));
	GPIO_vidSetPinValue(LCD_DATA_PORT,LCD_D3,GET_BIT(charCpy,3));
	GPIO_vidSetPinValue(LCD_DATA_PORT,LCD_D4,GET_BIT(charCpy,4));
	GPIO_vidSetPinValue(LCD_DATA_PORT,LCD_D5,GET_BIT(charCpy,5));
	GPIO_vidSetPinValue(LCD_DATA_PORT,LCD_D6,GET_BIT(charCpy,6));
	GPIO_vidSetPinValue(LCD_DATA_PORT,LCD_D7,GET_BIT(charCpy,7));

	GPIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_HIGH);
	delay_milli(2);
	GPIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_LOW);
	delay_milli(2);
	GPIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_HIGH);
		delay_milli(2);

}

void LCD_vidWriteString(s8 * s8String) {	
	while(*s8String != '\0') {
		LCD_vidWriteCharacter(*s8String);
		*(s8String++);
	}
}

void LCD_vidWriteSizedString(s8 * s8String,u8 u8sizeCpy) {	
	u8 i = 0;
	do {
		LCD_vidWriteCharacter(*s8String);
		*(s8String++);
		i++;
	}while(u8sizeCpy > i);
}

void LCD_vidBlinkString(s8 * s8stringCpy,u8 u8timesCpy) {
	u8 i = 0;
	s8 * s8string;
	s8string = s8stringCpy;
	do {
		delay_milli(50);	
		while(*s8string != '\0') {
			LCD_vidWriteCharacter(*s8string);
			*(s8string++);
		}
		delay_milli(50);
		i++;
		LCD_vidSendCommand(LCD_CLEAR_SCREEN);
		s8string = s8stringCpy;
	}
	while (u8timesCpy > i);
}

void LCD_vidWriteNumber(u16 u16NumberCpy) {
	if(u16NumberCpy < 10) {
		LCD_vidWriteCharacter(u16NumberCpy+'0');
	}
	else {
		if (u16NumberCpy < 100) {
			LCD_vidWriteCharacter(u16NumberCpy/10+'0');
			LCD_vidWriteCharacter(u16NumberCpy%10+'0');
		}
		if  (u16NumberCpy < 1000) {
			LCD_vidWriteCharacter(u16NumberCpy/100+'0');
			LCD_vidWriteCharacter((u16NumberCpy%100)/10+'0');
			LCD_vidWriteCharacter((u16NumberCpy%100)%10+'0');
		}
	}
}

void LCD_vidGoToXY(u8 u8xCpy, u8 u8yCpy) {
	#define LCD_SET_CURSOR_LOCATION 0x80
	u8 u8address;
	switch(u8yCpy) {
		case 0:
			u8address = u8xCpy;
			break;
		case 1:
			u8address = u8xCpy+0xC0;
			break;
		case 2:
			u8address = u8xCpy+0x94;
			break;
		case 3:
			u8address = u8xCpy+0xD4;
			break;
	}
	LCD_vidSendCommand(u8address | 0x80);
}

#define SET_CURSOR_LOCATION
void LCD_vidCreateCustomChar(u8 * u8CharPtrCpy, u8 u8LocationCpy) {
	u8 i = 0;
	LCD_vidSendCommand(0x40+(u8LocationCpy*8)); /*Setting to CGRAM address8*/
	while (i != 8) {
		LCD_vidWriteCharacter(*u8CharPtrCpy++);
		i++;
	}
	LCD_vidWriteCharacter(0x00+u8LocationCpy);
}

void LCD_vidWriteCustomChar(u8 u8LocationCpy) {
	LCD_vidWriteCharacter(0x00+u8LocationCpy);
}

/*This function has been reedited to allow writing a character
 *on a specific row and a specific column.
 * */
void LCD_vidWriteInPlace(u8 u8xCpy,u8 u8yCpy, u8 u8CharCpy) {
	LCD_vidGoToXY(u8xCpy,u8yCpy);
	LCD_vidWriteCharacter(u8CharCpy);
}

void delay_milli(int n) {
	int i, j;
	for (i = 0;  i < n; i++) {
		for (j = 0; j < 3180; j++) {
		}
}
}