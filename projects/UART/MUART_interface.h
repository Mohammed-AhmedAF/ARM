#ifndef _MUART_INTERFACE_H
#define _MUART_INTERFACE_H

void MUART_vidInit(void);
void MUART_vidSendByte(u8);
void MUART_u8ReceivByte(void);
void MUART_vidSendString(u8*);

#endif
