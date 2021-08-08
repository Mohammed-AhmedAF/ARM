#ifndef _UART0_INTERFACE_H
#define _UART0_INTERFACE_H

/*Struct to hold configuration of UART*/
typedef struct 
{
	u8 u8Fraction;
	u8 u8WordLength;
	u8 u8ClockSource;
	u8 u8RxTx;
	u8 u8FIFOEnabled;
	u8 u8InterruptEnabled;
	u8 u8HighSpeedEnabled;
	u16 u16Integer;
	void (*ptrF) (void);
} UARTConfig_t;

/*Macros used in configuration*/
#define UART_CLOCKSOURCE_RC 0
#define UART_CLOCKSOURCE_PIOSC 1

#define UART_WORDSIZE_8 0
#define UART_WORDSIZE_7 1
#define UART_WORDSIZE_6 2
#define UART_WORDSIZE_5 3

#define UART_FIFO_DISABLED 0
#define UART_FIFO_ENABLED 1

#define UART_INTERRUPT_DISABLED 0
#define UART_INTERRUPT_ENABLED 1

#define UART_RXTX_BOTH 0
#define UART_RXTX_RX_ONLY 1
#define UART_RXTX_TX_ONLY 2

/*High speed enabled HSE (Bit 5)*/
#define UART_HIGHSPEED_TRUE 1
#define UART_HIGHSPEED_FALSE 0
#define UART_HIGHSPEED_DIV8 UART_HIGHSPEED_TRUE
#define UART_HIGHSPEED_DIV16 UART_HIGHSPEED_FALSE
#define UART_HIGHSPEED_DIV_8 UART_HIGHSPEED_TRUE
#define UART_HIGHSPEED_DIV_16 UART_HIGHSPEED_FALSE

/*UART0*/
void UART0_vidInit(UARTConfig_t * UARTConfig);
void UART0_vidSendByte(u8 data);
char UART0_Receiver(void);
char UART0_u8GetReceivedByte(void);
void UART0_vidSendString(char *str);
void UART0_vidPutISRFunction(void(*ptrF)(void));

/*UART1*/
void UART1_vidInit(UARTConfig_t * UARTConfig);
void UART1_vidSendByte(u8 data);
char UART1_Receiver(void);
char UART1_u8GetReceivedByte(void);
void UART1_vidSendString(char *str);
void UART1_vidPutISRFunction(void(*ptrF)(void));
void UART_vidSendNumber(void (*ptrF) (u8),u16 u16Number);

/*UART2*/
void UART2_vidInit(UARTConfig_t * UARTConfig);
void UART2_vidSendByte(u8 data);
char UART2_Receiver(void);
char UART2_u8GetReceivedByte(void);
void UART2_vidSendString(char *str);
void UART2_vidPutISRFunction(void(*ptrF)(void));




#endif
