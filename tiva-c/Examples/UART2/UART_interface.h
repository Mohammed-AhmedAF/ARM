#ifndef _UART_INTERFACE_H
#define _UART_INTERFACE_H

/*Struct to hold configuration of UART*/
typedef struct 
{
	u8 u8Integer;
	u8 u8Fraction;
	u8 u8WordLength;
	u8 u8ClockSource;
} UARTConfig_t;


/*Function definitions*/
void UART_vidInit(UARTConfig_t *);
void UART_vidSendByte(u8 u8Byte);
u8 UART_u8ReceiveByte(void);
void UART_vidSendString(u8*);
void UART_vidPutISRFunction(void (*ptrFunc) (void));
u8 UART_u8GetReceivedByte(void);

/*Macros used in configuration*/
#define UART_CLOCKSOURCE_RC 0
#define UART_CLOCKSOURCE_PIOSC 1

#define UART_WORDSIZE_8 0
#define UART_WORDSIZE_7 1
#define UART_WORDSIZE_6 2
#define UART_WORDSIZE_5 3

#endif
