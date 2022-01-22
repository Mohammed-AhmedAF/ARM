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

/*UART3*/
void UART3_vidInit(UARTConfig_t * UARTConfig);
void UART3_vidSendByte(unsigned char data);
char UART3_Receiver(void);
void UART3_vidPutISRFunction(void(*ptrF)(void));
char UART3_u8GetReceivedByte(void);
void UART3_vidSendString(char *str);

/*UART4*/
void UART4_vidInit(UARTConfig_t * UARTConfig);
void UART4_vidSendByte(unsigned char data);
char UART4_Receiver(void);
void UART4_vidPutISRFunction(void(*ptrF)(void));
char UART4_u8GetReceivedByte(void);
void UART4_vidSendString(char *str);

/*UART5*/
void UART5_vidInit(UARTConfig_t * UARTConfig);
void UART5_vidSendByte(unsigned char data);
char UART5_Receiver(void);
void UART5_vidPutISRFunction(void(*ptrF)(void));
char UART5_u8GetReceivedByte(void);
void UART5_vidSendString(char *str);

/*UART6*/
void UART6_vidInit(UARTConfig_t * UARTConfig);
void UART6_vidSendByte(unsigned char data);
char UART6_Receiver(void);
void UART6_vidPutISRFunction(void(*ptrF)(void));
char UART6_u8GetReceivedByte(void);
void UART6_vidSendString(char *str);

/*UART7*/
void UART7_vidInit(UARTConfig_t * UARTConfig);
void UART7_vidSendByte(unsigned char data);
char UART7_Receiver(void);
void UART7_vidPutISRFunction(void(*ptrF)(void));
char UART7_u8GetReceivedByte(void);
void UART7_vidSendString(char *str);

#endif
