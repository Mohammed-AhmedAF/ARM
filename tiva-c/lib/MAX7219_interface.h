#ifndef _MAX7219_INTERFACE_H
#define _MAX7219_INTERFACE_H

/*Function declarations*/
void MAX7219_vidInit(void);
static void MAX7219_vidWriteByte(u8 u8Byte);
void MAX7219_vidWriteMax(u8 u8Address,u8 u8Data);
void MAX7219_vidClear(void);

#endif