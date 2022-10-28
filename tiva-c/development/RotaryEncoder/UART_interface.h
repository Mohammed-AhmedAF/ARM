#ifndef _UART0_INTERFACE_H
#define _UART0_INTERFACE_H

/*Struct to hold configuration of UART*/
typedef struct 
{
	u8 u8Module;
	u8 u8Fraction;
	u8 u8WordLength;
	u8 u8ClockSource;
	u8 u8RxTx;
	u8 u8ParityEnable;
	u8 u8ParitySelect;
	u8 u8FIFOEnabled;
	u8 u8FlowControl;
	u8 u8Loopback;
	u8 u8InterruptEnabled;
	u8 u8HighSpeedEnabled;
	u8 u8StopBits;
	u16 u16Integer;
	void (*ptrFHandlerReceive) (void);
	void (*ptrFHandlerTransmit) (void);
	void (*ptrFHandlerParity) (void);
} UARTConfig_t;

/*Macros used in configuration*/
#define UART_CLOCKSOURCE_RC 0
#define UART_CLOCKSOURCE_PIOSC 1

#define UART_FLOWCONTROL_CTS_ENABLED 2 
#define UART_FLOWCONTROL_CTS_DISABLED 4
#define UART_FLOWCONTROL_RTS_ENABLED 1
#define UART_FLOWCONTROL_RTS_DISABLED 0

#define UART_LOOPBACK_ENABLED 1
#define UART_LOOPBACK_DISABLED 0

#define UART_WORDSIZE_8 0
#define UART_WORDSIZE_7 1
#define UART_WORDSIZE_6 2
#define UART_WORDSIZE_5 3

#define UART_FIFO_DISABLED 0
#define UART_FIFO_ENABLED 1

#define UART_INTERRUPT_DISABLED 0
#define UART_INTERRUPT_ENABLED 1

#define UART_PARITY_DISABLED 0
#define UART_PARITY_ENABLED 1
#define UART_PARITY_SELECT_ODD 0
#define UART_PARITY_SELECT_EVEN 1

#define UART_STOPBITS_1 0
#define UART_STOPBITS_2 1

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

#define UART_INTEGER_16MHZ_9600 104
#define UART_FRACTION_16MHZ_9600 11
#define UART_INTEGER_16MHZ_19200 52
#define UART_FRACTION_16MHZ_19200 5
#define UART_INTEGER_16MHZ_38400 26
#define UART_FRACTION_16MHZ_38400 3

#define UART_MODULE_0 0
#define UART_MODULE_1 1
#define UART_MODULE_2 2
#define UART_MODULE_3 3
#define UART_MODULE_4 4 
#define UART_MODULE_5 5
#define UART_MODULE_6 6
#define UARt_MODULE_7 7

/*Bit definitions*/
#define UART_INTERRUPT_RX (1<<4)
#define UART_INTERRUPT_TX (1<<5)
#define UART_INTERRUPT_PARITY (1<<8)


void UART_vidInit(UARTConfig_t * const UARTConfig);
void UART_vidSendNumber(void (*ptrF) (u8),u16 u16Number);

/*UART0*/
void UART0_vidInit(UARTConfig_t * const UARTConfig);
void UART0_vidSendByte(u8 data);
char UART0_Receiver(void);
char UART0_u8GetReceivedByte(void);
void UART0_vidSendString(char *str);
void UART0_vidPutISRFunction(u8 u8InterruptSource,void(*ptrF)(void));

/*UART1*/
#ifdef USED_UART1
void UART1_vidInit(UARTConfig_t * const UARTConfig);
void UART1_vidSendByte(u8 data);
char UART1_Receiver(void);
char UART1_u8GetReceivedByte(void);
void UART1_vidSendString(char *str);
void UART1_vidPutISRFunction(u8 u8InterruptSource,void(*ptrF)(void));
void UART_vidSendNumber(void (*ptrF) (u8),u16 u16Number);
#endif

/*UART2*/
#ifdef USED_UART2
void UART2_vidInit(UARTConfig_t * const UARTConfig);
void UART2_vidSendByte(u8 data);
char UART2_Receiver(void);
char UART2_u8GetReceivedByte(void);
void UART2_vidSendString(char *str);
void UART2_vidPutISRFunction(u8 u8InterruptSource,void(*ptrF)(void));
#endif

/*UART3*/
#ifdef USED_UART3
void UART3_vidInit(UARTConfig_t * const UARTConfig);
void UART3_vidSendByte(unsigned char data);
char UART3_Receiver(void);
void UART3_vidPutISRFunction(u8 u8InterruptSource,void(*ptrF)(void));
char UART3_u8GetReceivedByte(void);
void UART3_vidSendString(char *str);
#endif

/*UART4*/
#ifdef USED_UART4
void UART4_vidInit(UARTConfig_t * const UARTConfig);
void UART4_vidSendByte(unsigned char data);
char UART4_Receiver(void);
void UART4_vidPutISRFunction(u8 u8InterruptSource,void(*ptrF)(void));
char UART4_u8GetReceivedByte(void);
void UART4_vidSendString(char *str);
#endif

/*UART5*/
#ifdef USED_UART5
void UART5_vidInit(UARTConfig_t * const UARTConfig);
void UART5_vidSendByte(unsigned char data);
char UART5_Receiver(void);
void UART5_vidPutISRFunction(u8 u8InterruptSource,void(*ptrF)(void));
char UART5_u8GetReceivedByte(void);
void UART5_vidSendString(char *str);
#endif

/*UART6*/
#ifdef USED_UART6
void UART6_vidInit(UARTConfig_t * const UARTConfig);
void UART6_vidSendByte(unsigned char data);
char UART6_Receiver(void);
void UART6_vidPutISRFunction(u8 u8InterruptSource,void(*ptrF)(void));
char UART6_u8GetReceivedByte(void);
void UART6_vidSendString(char *str);
#endif

/*UART7*/
#ifdef USED_UART7
void UART7_vidInit(UARTConfig_t * const UARTConfig);
void UART7_vidSendByte(unsigned char data);
char UART7_Receiver(void);
void UART7_vidPutISRFunction(u8 u8InterruptSource,void(*ptrF)(void));
char UART7_u8GetReceivedByte(void);
void UART7_vidSendString(char *str);
#endif

#endif
