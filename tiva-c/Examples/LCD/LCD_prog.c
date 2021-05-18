#include "TM4C123.h"                    // Device header
#include "LCD_interface.h"

void  LCD_vidInit(void) {
	SYSCTL->RCGCGPIO = 0x01; //Command pins (PORT A)
	SYSCTL->RCGCGPIO |= 0x02; //Data pins (PORT B)
	
	GPIOA->DIR |= 0xE0; //0x11100000 controls RS,RW,E pins
	GPIOA->DEN |= 0xE0;
	
	GPIOB->DIR |= 0xFF;
	GPIOB->DEN |= 0xFF;
		
	 /*Return Home*/
	LCD_vidSendCommand(LCD_CLEAR_SCREEN); /*Clear screen*/
  LCD_vidSendCommand(LCD_RETURN_HOME);
	LCD_vidSendCommand(0b00000110); /*Set entry mode*/
	LCD_vidSendCommand(0b00001100); /*Display On/Off control*/
  LCD_vidSendCommand(0b00111000); /*Function Set*/
}

void LCD_vidSendCommand(unsigned char u8CommandCpy) {
	GPIOA->DATA = 0x00; //RS, RW, E are all zeros.
	GPIOB->DATA = u8CommandCpy; //Sending command bits
	GPIOA->DATA |= 0x80; //So E = 1
	delay_milli(2);
	GPIOA->DATA |= 0x00;
	if (u8CommandCpy < 4) {
		delay_milli(2);
	}
	else {
		delay_milli(2);
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