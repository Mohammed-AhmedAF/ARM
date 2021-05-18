#include "Std_Types.h"
#include "Macros.h"
#include "UART_private.h"
#include "UART_interface.h"

void (*UART_vidCallBack) (void);


void UART_vidPutISRFunction(void (*ptrFunc) (void))
{
	UART_vidCallBack = ptrFunc;
}

void UART_vidInit(UARTConfig_t * UARTConfig)
{

	/*Disabling first*/
	UART0_CTL = 0;
	
	/*Configuring baudrate*/
	UART0_IBRD = UARTConfig->u8Integer;
	UART0_FBRD = UARTConfig->u8Fraction;
	
	/*Clock source selection*/
	switch(UARTConfig->u8ClockSource)
	{
		case UART_CLOCKSOURCE_RC:
		UART0_CC = 0;
		break;
		case UART_CLOCKSOURCE_PIOSC:
			UART0_CC = 0x05;
		break;
	}
	
	/*Frame size*/
	switch (UARTConfig->u8WordLength)
	{
		case UART_WORDSIZE_8:
		UART0_LCRH = 0x60;
		break;
		case UART_WORDSIZE_7:
		UART0_LCRH = 0x40;
		break;
		case UART_WORDSIZE_6:
			UART0_LCRH = 0x20;
		break;
		case UART_WORDSIZE_5:
			UART0_LCRH = 0x00;
		break;
	}
	/*Enable transmission*/
	/*Enable UART*/
	SET_BIT(UART0_CTL,0);
	
	
	SET_BIT(UART0_CTL,8);
	SET_BIT(UART0_CTL,9);

	
	/*Enable interrupt*/
	UART0_IM |= 0x0010;
	
}
	
void UART_vidSendByte(u8 u8Byte)
{
	while(GET_BIT(UART0_FR,5) == 1);
	UART0_DATA = u8Byte;
}

u8 UART_u8ReceiveByte(void)
{
	while(GET_BIT(UART0_FR,4) == 1);
	return UART0_DATA;
}

u8 UART_u8GetReceivedByte(void)
{
	return UART0_DATA;
}

void UART_vidSendString(u8 * pu8Message)
{
	do {
		UART_vidSendByte(*pu8Message);
	}while(*pu8Message++ != '\0');
	
}

void UART0_Handler()
{
	UART_vidCallBack();
	UART0_ICR = 0x0010;
}
