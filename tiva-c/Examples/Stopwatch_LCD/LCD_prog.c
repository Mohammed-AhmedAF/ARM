#include "STD_TYPES.h"

#include "TM4C123GH6PM.h"                    // Device header

#include "LCD_interface.h"

void  LCD_vidInit(void) {
	
	GPIOA->DIR |= 0xE0; //0x11100000 controls RS,RW,E pins
	GPIOA->DEN |= 0xE0;
	
	GPIOB->DIR |= 0xFF;
	GPIOB->DEN |= 0xFF;
		
	 /*Return Home*/
	LCD_vidSendCommand(LCD_CLEAR_SCREEN); /*Clear screen*/
  LCD_vidSendCommand(LCD_RETURN_HOME);
	LCD_vidSendCommand(0b00000110); /*Set entry mode*/
	LCD_vidSendCommand(0b00001100); /*Display On/Off control*/
  LCD_vidSendCommand(LCD_FUNCTION_SET|LCD_8BIT|LCD_4LINES); /*Function Set*/
	
}

void LCD_vidSendCommand(unsigned char u8CommandCpy) {
	GPIOA->DATA = 0x00; //RS, RW, E are all zeros.
	GPIOB->DATA = u8CommandCpy; //Sending command bits
	GPIOA->DATA = 0x80; //So E = 1
	delay_micro(0);
	GPIOA->DATA = 0x00;
	if (u8CommandCpy < 4) {
		delay_milli(2);
	}
	else {
		delay_milli(2);
	}
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

void LCD_vidWriteCharacter(char u8CharacterCpy) {
	GPIOA->DATA = 0x20; //RS = 1, RW = 0
	GPIOB->DATA = u8CharacterCpy;
	GPIOA->DATA |= 0x80;
	delay_milli(2);
	GPIOA->DATA |= 0x00;
	delay_micro(2);
}
void LCD_vidWriteString(char * String) {
	while(*String != '\0') {
		LCD_vidWriteCharacter(*String);
		*String++;
	}
}

void LCD_vidGoToXY(u8 u8xCpy, u8 u8yCpy) {
#define LCD_SET_CURSOR_LOCATION 0x80
	u8 u8address = u8xCpy;
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
	LCD_vidSendCommand(LCD_RETURN_HOME);
	LCD_vidSendCommand(u8address | 0x80);
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