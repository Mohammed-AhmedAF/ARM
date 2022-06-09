/*
 * Author: Mohamed Ahmed Abd Al-Fattah
 */

#ifndef _LCD_INTERFACE_H
#define _LCD_INTERFACE_H

#define LCD_DATA_PORT GPIO_PORTB
#define LCD_CTRL_PORT GPIO_PORTA

#define LCD_D0 0
#define LCD_D1 1
#define LCD_D2 2
#define LCD_D3 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

#define LCD_8MODE_2L 0x38
#define LCD_ON_NOCURSOR 0x0C
#define LCD_CLEAR_SCREEN 0b00000001
#define LCD_RETURN_HOME 0b00000010

#define LCD_ENTRY_MODE 0b00000110
#define LCD_DISPLAY_CONTROL 0b00001100
#define LCD_FUNCTION_SET 0b00111000


#define LCD_MOVE_CURSOR_LEFT 0x14

#define LCD_E 7
#define LCD_RW 6
#define LCD_RS 5

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
/*This macro is used to shift the clock digits
 *on LCD row.
 * */
#define  LCD_XPOS_SHIFT 5

/*Function definitions*/
void LCD_vidInit(void);
void LCD_vidSendCommand(u8);
void LCD_vidWriteCharacter(u8);
void LCD_vidWriteString(s8*);
void LCD_vidBlinkString(s8*,u8);
void LCD_vidWriteSizedString(s8*,u8);
void LCD_vidGoToXY(u8,u8);
void LCD_vidWriteNumber(u16);
void LCD_vidWriteInPlace(u8,u8,u8);

void delay_milli(int);
#endif
