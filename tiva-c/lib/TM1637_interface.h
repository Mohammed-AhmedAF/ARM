#ifndef _TM1637_INTERFACE_H
#define _TM1637_INTERFACE_H

/*Function definitions*/
void TM1637_vidInit(void);
static void TM1637_vidStart(void);
static void TM1637_vidStop(void);
static void TM1637_vidSetClkHigh(void);
static void TM1637_vidSetClkLow(void);
static void TM1637_vidSetDIOHigh(void);
static void TM1637_vidSetDIOLow(void);
static u8 TM1637_u8ReadResult(void);
static void TM1637_vidWriteByte(u8 u8Byte);
static void TM1637_vidDelay(u8 u8DelayVal);
void TM1637_vidDisplayDecimal(u32 u32Val, u8 u8DisplaySeparator);
void TM1637_vidSetBrightness(u8 u8BrightnessLevel);
void TM1637_vidDelayM(u32 u32DelayVal);
void TM1637_vidDisplayChar(u8 u8Char);
void TM1637_vidDisplayTemperatur(u32 u32Val, u8 u8DisplaySeparator);
void TM1637_vidDisplayDigit(u8 u8Digit, u8 u8Position, u8 u8DisplayPosition);
void TM1637_vidDisplayTwoDigitsRight(u8 u8Number,u8 u8DisplaySeparator);
void TM1637_vidDisplayTwoDigitssLeft(u8 u8Number);

/*Macros*/
#define TM1637_SEPARATOR_DISABLED 0
#define TM1637_SEPARATOR_ENABLED 1
#define TM1637_POS_0 0
#define TM1637_POS_1 1
#define TM1637_POS_2 2
#define TM1637_POS_3 3

#endif