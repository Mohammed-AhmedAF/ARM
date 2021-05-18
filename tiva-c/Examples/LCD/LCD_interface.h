#ifndef _LCD_INTERFACE_H
#define _LCD_INTERFACE_H

#define LCD_CLEAR_SCREEN 0x01
#define LCD_RETURN_HOME 0x02

void LCD_vidInit(void);
void LCD_vidSendCommand(unsigned char);
void LCD_vidWriteCharacter(char);
void LCD_vidWriteString(char*);
void delay_micro(int);
void delay_milli(int);

#endif