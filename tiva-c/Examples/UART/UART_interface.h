#ifndef _UART_INTERFACE_H
#define _UART_INTERFACE_H

/*Function definitions*/
void UART_vidInit(void);
void UART_vidSendByte(u8 u8Byte);
u8 UART_u8ReceiveByte(void);
void UART_vidSendString(u8*);

#endif
