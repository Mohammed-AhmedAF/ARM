#ifndef _LCD_INTERFACE_H
#define _LCD_INTERFACE_H

void LCD_vidInit(void);
void LCD_vidWriteCharacter(u8 u8Char);
void LCD_vidSendCommand(u8 u8Command);
void LCD_vidWriteNumber(u16 u16NumberCpy);
void LCD_vidWriteString(s8 * s8String);

/*Helper delay functions*/
void delay_micro(int n);
void  delay_milli(int n);

#define LCD_PORT_D4 GPIO_PORTA
#define LCD_PORT_D5 GPIO_PORTA
#define LCD_PORT_D6 GPIO_PORTA
#define LCD_PORT_D7 GPIO_PORTA

#define LCD_PIN_D4 GPIO_PIN4
#define LCD_PIN_D5 GPIO_PIN5
#define LCD_PIN_D6 GPIO_PIN6
#define LCD_PIN_D7 GPIO_PIN7

#define LCD_PORT_RS GPIO_PORTB
#define LCD_PORT_RW GPIO_PORTB
#define LCD_PORT_EN GPIO_PORTB

#define LCD_PIN_RS GPIO_PIN0
#define LCD_PIN_RW GPIO_PIN1
#define LCD_PIN_EN GPIO_PIN2

#define LCD_8MODE_2L 0x38
#define LCD_ON_NOCURSOR 0x0C
#define LCD_CLEAR_SCREEN 0b00000001
#define LCD_RETURN_HOME 0b00000010

/*Entry mode*/
#define LCD_SET_ENTRY_MODE 0x04
#define LCD_MOVE_CURSOR_RIGHT 0x02
#define LCD_MOVE_CURSOR_LEFT 0x00
#define LCD_DISPLAY_SHIFT_ON 0x01
#define LCD_DISPLAY_SHIFT_OFF 0x00


/*Display on/off control */
#define LCD_DISPLAY_ON 0x0C
#define LCD_DISPLAY_OFF 0x08

#define LCD_CURSOR_ON 0x0A
#define LCD_CURSOR_OFF 0x08

#define LCD_CURSOR_BLINK_ON 0x09
#define LCD_CURSOR_BLINK_OFF 0x08

/*Function set*/
#define LCD_FUNCTION_SET 0x20
#define LCD_8BIT 0x10
#define LCD_4BIT 0x00
#define LCD_4LINES 0x08

#endif