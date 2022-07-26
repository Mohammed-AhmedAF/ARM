#ifndef _LCD_INTERFACE_H
#define _LCD_INTERFACE_H

void LCD_vidInit(void);
void LCD_vidSendCommand(u8 u8Command);
void LCD_vidWriteCharacter(u8 u8Character);
void LCD_vidSetCursor(u8 u8xPos, u8 u8yPos);
void delayMilli(u32 u32Milli);
void LCD_vidClearScreen(void);

#endif