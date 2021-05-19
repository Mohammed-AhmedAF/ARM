#include "STD_TYPES.h"
#include "Macros.h"
#include "UART_private.h"
#include "UART_interface.h"

void UART_vidInit(void)
{

	/*Disabling first*/
	UART0_CTL = 0;
	
	/*Configuring baudrate*/
	UART0_IBRD = 104;
	UART0_FBRD = 11;
	
	UART0_CC = 0;
	
	/*Frame size*/
	UART0_LCRH = 0x60;

	/*Enable transmission*/
	/*Enable UART*/
	SET_BIT(UART0_CTL,0);
	
	
	SET_BIT(UART0_CTL,8);
	SET_BIT(UART0_CTL,9);

}
	
void UART_vidSendByte(u8 u8Byte)
{
	while(GET_BIT(UART0_FR,5) == 1);
	UART0_DATA = u8Byte;
}

u8 UART_u8ReceiveByte(void)
{
	while(GET_BIT(UART0_FR,4) == 1);
	return (u8) UART0_DATA;
}

void UART_vidSendString(u8 * pu8Message)
{
	do {
		UART_vidSendByte(*pu8Message);
	}while(*pu8Message++ != '\0');
	
}