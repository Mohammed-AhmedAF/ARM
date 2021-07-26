#ifndef _LCD_INTERFACE_H
#define _LCD_INTERFACE_H

#define LCD_CLEAR_SCREEN 0x01
#define LCD_RETURN_HOME 0x02

#define LCD_FUNCTION_SET 0x20
#define LCD_8BIT 0x10
#define LCD_4BIT 0x00
#define LCD_4LINES 0x08

/*Macros defined to be used with the GoTOXY function*/
#define LCD_XPOS0 0
#define LCD_XPOS1 1
#define LCD_XPOS2 2
#define LCD_XPOS3 3
#define LCD_XPOS4 4
#define LCD_XPOS5 5
#define LCD_XPOS6 6
#define LCD_XPOS7 7
#define LCD_XPOS8 8
#define LCD_XPOS9 9
#define LCD_XPOS10 10
#define LCD_XPOS11 11
#define LCD_XPOS12 12
#define LCD_XPOS13 13
#define LCD_XPOS14 14
#define LCD_XPOS15 15
#define LCD_XPOS16 16
#define LCD_XPOS17 17
#define LCD_XPOS18 18
#define LCD_XPOS19 19

#define LCD_YPOS0 0
#define LCD_YPOS1 1
#define LCD_YPOS2 2
#define LCD_YPOS3 3

void LCD_vidInit(void);
void LCD_vidSendCommand(unsigned char);
void LCD_vidWriteCharacter(char);
void LCD_vidWriteString(char*);
void LCD_vidWriteNumber(u16 u16Number);
void LCD_vidGoToXY(u8 u8xCpy, u8 u8yCpy);
void delay_micro(int);
void delay_milli(int);

#endif