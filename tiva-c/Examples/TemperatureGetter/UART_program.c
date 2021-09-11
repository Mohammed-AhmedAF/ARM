#include "Macros.h"
#include "STD_TYPES.h"
#include "TM4C123.h"
#include "UART_interface.h"

void (*UART0_callback) (void);
void (*UART1_callback) (void);
void (*UART2_callback) (void);


void UART0_vidInit(UARTConfig_t * UARTConfig)
{
		UART0->CTL = 0;         /* UART5 module disbable */
	
    UART0->IBRD = UARTConfig->u16Integer;      /* for 9600 baud rate, integer = 104 */
    UART0->FBRD = UARTConfig->u8Fraction;       /* for 9600 baud rate, fractional = 11*/
	
		/*select system clock*/
		if (UARTConfig->u8ClockSource == UART_CLOCKSOURCE_RC)
		{
			UART0->CC |= 0; 
		}
		else
		{
			UART0->CC = 0x5;
		}
		UART0->DR &= 0;
		
		if (UARTConfig->u8FIFOEnabled)
		{
			SET_BIT(UART0->LCRH,4);
		}
		else
		{
			CLEAR_BIT(UART0->LCRH,4);
		}
	
		/*Data length*/
		switch(UARTConfig->u8WordLength)
		{
			case UART_WORDSIZE_5:
				UART0->LCRH = 0x00;
				break;
			case UART_WORDSIZE_6:
				UART0->LCRH = 0x20;
				break;
			case UART_WORDSIZE_7:
				UART0->LCRH = 0x40;
				break;
			case UART_WORDSIZE_8:
				UART0->LCRH = 0x60;     /* data lenght 8-bit, not parity bit, no FIFO */
				break;
		
		}
		
		if (UARTConfig->u8HighSpeedEnabled == UART_HIGHSPEED_FALSE)
		{
			CLEAR_BIT(UART0->CTL,5);
		}
		else
		{
			SET_BIT(UART0->CTL,5);

		}
		
		/*Select Rx or TX or bot to be enabled*/
		switch(UARTConfig->u8RxTx)
		{
			case UART_RXTX_BOTH:
				SET_BIT(UART0->CTL,8);
				SET_BIT(UART0->CTL,9);
				break;
			case UART_RXTX_RX_ONLY:
						SET_BIT(UART0->CTL,9);
				break;
			case UART_RXTX_TX_ONLY:
				SET_BIT(UART0->CTL,8);
			break;
		}
		
		/*Enabled UART*/
		SET_BIT(UART0->CTL,0);
	
		if (UARTConfig->u8InterruptEnabled)
		{
			/*Receive interrupt*/
			SET_BIT(UART0->IM,4);
		}
		else
		{
			CLEAR_BIT(UART0->IM,4);
		}
		
		/*Function to be executed when interrupt occurs*/
		if (UARTConfig->u8InterruptEnabled)
		{
			UART0_vidPutISRFunction(UARTConfig->ptrF);
		}
		else
		{
		
		}
}

void UART0_vidPutISRFunction(void(*ptrF)(void))
{
	UART0_callback = ptrF;
}

void UART0_vidSendByte(unsigned char data)  
{
    while((UART0->FR & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART0->DR = data;                  /* before giving it another byte */
}

char UART0_Receiver(void)  
{
    char data;
	  while((UART0->FR & (1<<4)) != 0); /* wait until Rx buffer is not full */
    data = (char) UART0->DR ;  	/* before giving it another byte */
    return (unsigned char) data; 
}

char UART0_u8GetReceivedByte(void)
{
	return (u8) UART0->DR;
}
void UART0_vidSendString(char *str)
{
  while(*str)
	{
		UART0_vidSendByte(*(str++));
	}
}

void UART0_Handler()
{
	UART0_callback();
	UART0->ICR = 0x0010;
}


void UART1_vidInit(UARTConfig_t * UARTConfig)
{
		UART1->CTL = 0;         /* UART5 module disbable */
	
    UART1->IBRD = UARTConfig->u16Integer;      /* for 9600 baud rate, integer = 104 */
    UART1->FBRD = UARTConfig->u8Fraction;       /* for 9600 baud rate, fractional = 11*/
	
		/*select system clock*/
		if (UARTConfig->u8ClockSource == UART_CLOCKSOURCE_RC)
		{
			UART1->CC |= 0; 
		}
		else
		{
			UART1->CC = 0x5;
		}
		UART1->DR &= 0;
		
		if (UARTConfig->u8FIFOEnabled)
		{
			SET_BIT(UART1->LCRH,4);
		}
		else
		{
			CLEAR_BIT(UART1->LCRH,4);
		}
	
		/*Data length*/
		switch(UARTConfig->u8WordLength)
		{
			case UART_WORDSIZE_5:
				UART1->LCRH = 0x00;
				break;
			case UART_WORDSIZE_6:
				UART1->LCRH = 0x20;
				break;
			case UART_WORDSIZE_7:
				UART1->LCRH = 0x40;
				break;
			case UART_WORDSIZE_8:
				UART1->LCRH = 0x60;     /* data lenght 8-bit, not parity bit, no FIFO */
				break;
		
		}
		
		if (UARTConfig->u8HighSpeedEnabled == UART_HIGHSPEED_FALSE)
		{
			CLEAR_BIT(UART1->CTL,5);
		}
		else
		{
			SET_BIT(UART1->CTL,5);

		}
		
		/*Select Rx or TX or bot to be enabled*/
		switch(UARTConfig->u8RxTx)
		{
			case UART_RXTX_BOTH:
				SET_BIT(UART1->CTL,8);
				SET_BIT(UART1->CTL,9);
				break;
			case UART_RXTX_RX_ONLY:
						SET_BIT(UART1->CTL,9);
				break;
			case UART_RXTX_TX_ONLY:
				SET_BIT(UART1->CTL,8);
			break;
		}
		
		/*Enabled UART*/
		SET_BIT(UART1->CTL,0);
	
		if (UARTConfig->u8InterruptEnabled)
		{
			/*Receive interrupt*/
			SET_BIT(UART1->IM,4);
		}
		else
		{
			CLEAR_BIT(UART1->IM,4);
		}
		
		/*Function to be executed when interrupt occurs*/
		if (UARTConfig->u8InterruptEnabled)
		{
			UART1_vidPutISRFunction(UARTConfig->ptrF);
		}
		else
		{
		
		}
		
}

void UART1_vidPutISRFunction(void(*ptrF)(void))
{
	UART1_callback = ptrF;
}

void UART1_vidSendByte(unsigned char data)  
{
    while((UART1->FR & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART1->DR = data;                  /* before giving it another byte */
}

char UART1_Receiver(void)  
{
    char data;
	  while((UART1->FR & (1<<4)) != 0); /* wait until Rx buffer is not full */
    data = (char) UART1->DR ;  	/* before giving it another byte */
    return (unsigned char) data; 
}

char UART1_u8GetReceivedByte(void)
{
	return (u8) UART1->DR;
}
void UART1_vidSendString(char *str)
{
  while(*str)
	{
		UART1_vidSendByte(*(str++));
	}
}

void UART1_Handler()
{
	UART1_callback();
	UART1->ICR = 0x0010;
}

void UART2_vidInit(UARTConfig_t * UARTConfig)
{
		UART2->CTL = 0;         /* UART5 module disbable */
	
    UART2->IBRD = UARTConfig->u16Integer;      /* for 9600 baud rate, integer = 104 */
    UART2->FBRD = UARTConfig->u8Fraction;       /* for 9600 baud rate, fractional = 11*/
	
		/*select system clock*/
		if (UARTConfig->u8ClockSource == UART_CLOCKSOURCE_RC)
		{
			UART2->CC |= 0; 
		}
		else
		{
			UART2->CC = 0x5;
		}
		UART2->DR &= 0;
		
		if (UARTConfig->u8FIFOEnabled)
		{
			SET_BIT(UART2->LCRH,4);
		}
		else
		{
			CLEAR_BIT(UART2->LCRH,4);
		}
	
		/*Data length*/
		switch(UARTConfig->u8WordLength)
		{
			case UART_WORDSIZE_5:
				UART2->LCRH = 0x00;
				break;
			case UART_WORDSIZE_6:
				UART2->LCRH = 0x20;
				break;
			case UART_WORDSIZE_7:
				UART2->LCRH = 0x40;
				break;
			case UART_WORDSIZE_8:
				UART2->LCRH = 0x60;     /* data lenght 8-bit, not parity bit, no FIFO */
				break;
		
		}
		
		if (UARTConfig->u8HighSpeedEnabled == UART_HIGHSPEED_FALSE)
		{
			CLEAR_BIT(UART2->CTL,5);
		}
		else
		{
			SET_BIT(UART2->CTL,5);

		}
		
		/*Select Rx or TX or bot to be enabled*/
		switch(UARTConfig->u8RxTx)
		{
			case UART_RXTX_BOTH:
				SET_BIT(UART2->CTL,8);
				SET_BIT(UART2->CTL,9);
				break;
			case UART_RXTX_RX_ONLY:
						SET_BIT(UART2->CTL,9);
				break;
			case UART_RXTX_TX_ONLY:
				SET_BIT(UART2->CTL,8);
			break;
		}
		
		/*Enabled UART*/
		SET_BIT(UART2->CTL,0);
	
		if (UARTConfig->u8InterruptEnabled)
		{
			/*Receive interrupt*/
			SET_BIT(UART2->IM,4);
		}
		else
		{
			CLEAR_BIT(UART2->IM,4);
		}
}

void UART2_vidPutISRFunction(void(*ptrF)(void))
{
	UART2_callback = ptrF;
}

void UART2_vidSendByte(unsigned char data)  
{
    while((UART2->FR & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART2->DR = data;                  /* before giving it another byte */
}

char UART2_Receiver(void)  
{
    char data;
	  while((UART2->FR & (1<<4)) != 0); /* wait until Rx buffer is not full */
    data = (char) UART2->DR ;  	/* before giving it another byte */
    return (unsigned char) data; 
}

char UART2_u8GetReceivedByte(void)
{
	return (u8) UART2->DR;
}
void UART2_vidSendString(char *str)
{
  while(*str)
	{
		UART2_vidSendByte(*(str++));
	}
}

void UART2_Handler()
{
	UART2_callback();
	UART2->ICR = 0x0010;
}

void UART_vidSendNumber(void (*ptrF) (u8),u16 u16Number)
{
	if(u16Number < 10) {
		ptrF('0');
		ptrF(u16Number+'0');
	}
	else {
		if (u16Number < 100) {
			ptrF(u16Number/10+'0');
			ptrF(u16Number%10+'0');
		}
		else if (u16Number < 1000) {
			ptrF((u16Number/100)+'0');
			ptrF((u16Number%100)/10+'0');
			ptrF((u16Number%100)%10+'0');
		}
		else if (u16Number < 10000)
		{
			ptrF((u16Number/1000)+'0');
			ptrF((u16Number%1000)/100+'0');
			ptrF((u16Number%100)/10+'0');
			ptrF((u16Number%100)%10+'0');
		}
	}
}