#include "STD_TYPES.h"
#include "Macros.h"
#include "UART_private.h"
#include "UART_interface.h"

/*
 * CLK enabled for USART, if enabled receive will not work
 * with UART-USB dongle
 *
 */

void (*callback) (void);

void UART_vidInit(UARTConfig_t * uartConfigP) {
	switch(uartConfigP->u8WordSize)
	{
		case UART_WORDSIZE_8:
				CLEAR_BIT(MUART->CR1,12); /*Word length*/
			break;
	}
	CLEAR_BIT(MUART->CR1,11); /*UART Wake Up method*/
	CLEAR_BIT(MUART->CR1,10); /*Parity Control*/
	SET_BIT(MUART->CR1,5); /*Interrupt is enabled*/
	switch(uartConfigP->u8TxRx)
	{
		case UART_TXRX_TX_ONLY:
			SET_BIT(MUART->CR1,3); /*Transmitter is enabled*/
			break;
		case UART_TXRX_RX_ONLY:
			SET_BIT(MUART->CR1,2); /*Receiver is enabled*/
			break;
		case UART_TXRX_BOTH:
		SET_BIT(MUART->CR1,3); /*Transmitter is enabled*/
		SET_BIT(MUART->CR1,2); /*Receiver is enabled*/
		break;
	}
	
	CLEAR_BIT(MUART->CR2,11); /*Clock is disabled*/
	
	
	/*Baudrate: 0x0271 for 72 MHz System clock*/
	MUART->BRR = 0x0271; /*Baudrate, was 0x341*/

	SET_BIT(MUART->GTPR,3); /*Setting prescaler*/
	
	/*Interrupt handler*/
	UART_vidPutISRFunction(uartConfigP->ptrHandler);

	/*UART Enable*/
	SET_BIT(MUART->CR1,13); 
}

void UART_vidSendByte(u8 u8ByteCpy) {
	MUART->DR = u8ByteCpy;
	while (GET_BIT(MUART->SR,7) == 0); /*Checking Transmission Data Register Empty flag*/

}

u8 UART_u8ReceiveByte(void) {
	while (GET_BIT(MUART->SR,5) == 0); /*Checking Read Data Register not Empty*/
	return (MUART->DR & 0x1FF);
}

void UART_vidSendString(u8 * u8StringPtrCpy) {
	while (*u8StringPtrCpy != '\0') {
		UART_vidSendByte(*u8StringPtrCpy);
		u8StringPtrCpy++;
	}

}

void UART_vidSendNumber(u32 u16NumberCpy) {
	if(u16NumberCpy < 10) {
			UART_vidSendByte(u16NumberCpy+'0');
		}
		else {
			if (u16NumberCpy < 100) {
				UART_vidSendByte(u16NumberCpy/10+'0');
				UART_vidSendByte(u16NumberCpy%10+'0');
			}
			else if  (u16NumberCpy < 1000) {
				UART_vidSendByte(u16NumberCpy/100+'0');
				UART_vidSendByte((u16NumberCpy%100)/10+'0');
				UART_vidSendByte((u16NumberCpy%100)%10+'0');
			}
			else if (u16NumberCpy < 10000) {
				UART_vidSendByte((u16NumberCpy/1000)+'0');
				UART_vidSendByte((u16NumberCpy%1000)/100+'0');
				UART_vidSendByte(((u16NumberCpy%1000)%100)/10+'0');
				UART_vidSendByte((u16NumberCpy%1000)%10+'0');
			}
			else if (u16NumberCpy < 100000) {
				UART_vidSendByte((u16NumberCpy/10000)+'0');
				UART_vidSendByte((u16NumberCpy%10000)/1000+'0');
				UART_vidSendByte((u16NumberCpy%10000)%1000/100+'0');
				UART_vidSendByte((u16NumberCpy%10000)%1000%100/10+'0');
				UART_vidSendByte((u16NumberCpy%10000)%1000%100%10+'0');
			}
		}
}

void UART_vidPutISRFunction(void (*ptrF)(void))
{
	callback = ptrF;
}

u8 UART_u8GetReceivedByte(void)
{
	return MUART->DR;
}

void USART1_IRQHandler (void)
{
	callback();
}