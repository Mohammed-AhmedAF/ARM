#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MUART_private.h"
#include "MUART_interface.h"

void MUART_vidInit(void) {
	SET_BIT(MUART->CR1,13); /*UART Enable*/
	CLEAR_BIT(MUART->CR1,12); /*Word length*/
	CLEAR_BIT(MUART->CR1,11); /*UART Wake Up method*/
	CLEAR_BIT(MUART->CR1,10); /*Parity Control*/
	CLEAR_BIT(MUART->CR1,8); /*Interrupt is inhibited*/
	SET_BIT(MUART->CR1,3); /*Transmitter is enabled*/
	SET_BIT(MUART->CR1,2); /*Receiver is enabled*/
	SET_BIT(MUART->CR2,11); /*Clock is enabled*/
	MUART->BRR = 0x341; /**/

	SET_BIT(MUART->GTPR,3); /*Setting prescaler*/
}

void MUART_vidSendByte(u8 u8ByteCpy) {
	MUART->DR = u8ByteCpy;
	while (GET_BIT(MUART->SR,7) == 0); /*Checking Transmission Data Register Empty flag*/
}

u8 MUART_u8ReceiveByte(void) {
	while (GET_BIT(MUART->SR,5) == 0); /*Checking Read Data Register not Empty*/
	return MUART->DR;
}

void MUART_vidSendString(u8 * u8StringPtrCpy) {
	while (*u8StringPtrCpy != '\0') {
		MUART_vidSendByte(*u8StringPtrCpy);
		u8StringPtrCpy++;
	}

}
