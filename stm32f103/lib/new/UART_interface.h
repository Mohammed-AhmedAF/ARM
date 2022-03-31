#ifndef _MUART_INTERFACE_H
#define _MUART_INTERFACE_H

typedef struct
{
	u8 u8WordSize;
	u8 u8Interrupt;
	u8 u8TxRx;
	u32 u32Baudrate;
	void (*ptrHandler) (void);
} UARTConfig_t;

void UART_vidInit(UARTConfig_t * uartConfigP);
void UART_vidSendByte(u8);
void UART_u8ReceivByte(void);
void UART_vidSendString(u8*);
void UART_vidPutISRFunction(void (*ptrF)(void));
u8 UART_u8GetReceivedByte(void);


#define UART_WORDSIZE_8 0
#define UART_INTERRUPT_RX_ENABLED 0
#define UART_TXRX_TX_ONLY 0
#define UART_TXRX_RX_ONLY 1
#define UART_TXRX_BOTH 2


#endif
