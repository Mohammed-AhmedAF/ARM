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

#endif