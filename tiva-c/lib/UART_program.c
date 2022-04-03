#include "Macros.h"
#include "STD_TYPES.h"
#include "TM4C123.h"
#include "UART_config.h"
#include "UART_interface.h"

#ifdef USED_UART0
static void (*UART0_callback) (void);
static void (*UART0_callback_transmit)(void);
static void (*UART0_callback_parity) (void);
#endif
#ifdef USED_UART1
static void (*UART1_callback) (void);
static void (*UART1_callback_transmit) (void);
static void (*UART1_callback_parity) (void);
#endif

#ifdef USED_UART2
static void (*UART2_callback) (void);
static void (*UART2_callback_transmit) (void);
static void (*UART2_callback_parity) (void);
#endif

#ifdef USED_UART3
static void (*UART3_callback) (void);
static void (*UART3_callback_transmit) (void);
static void (*UART3_callback_parity) (void);
#endif 

#ifdef USED_UART4
static void (*UART4_callback) (void);
static void (*UART4_callback_transmit) (void);
static void (*UART4_callback_parity) (void);
#endif

#ifdef USED_UART5
static void (*UART5_callback) (void);
static void (*UART5_callback_transmit)(void);
static void (*UART5_callback_parity) (void);
#endif 

#ifdef USED_UART6
static void (*UART6_callback) (void);
static void (*UART6_callback_transmit)(void);
static void (*UART6_callback_parity) (void);
#endif

#ifdef USED_UART7
static void (*UART7_callback) (void);
static void (*UART7_callback_transmit)(void);
static void (*UART7_callback_parity) (void);
#endif


#ifdef USED_UART0
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
				UART0->LCRH |= 0x0<<5;
				break;
			case UART_WORDSIZE_6:
				UART0->LCRH |= 0x1<<5;
				break;
			case UART_WORDSIZE_7:
				UART0->LCRH |= 0x2<<5;
				break;
			case UART_WORDSIZE_8:
				UART0->LCRH |= 0x3<<5;
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
		
		/*Select Rx or TX or both to be enabled*/
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
		
		/*Parity configuration*/
		if (UARTConfig->u8ParityEnable == UART_PARITY_ENABLED)
		{
			SET_BIT(UART0->LCRH,1);
			/*Select parity*/
			if (UARTConfig->u8ParitySelect == UART_PARITY_SELECT_ODD)
			{
				CLEAR_BIT(UART0->LCRH,2);
			}
			else if (UARTConfig->u8ParitySelect == UART_PARITY_SELECT_EVEN)
			{
				SET_BIT(UART0->LCRH,2);
			}
		}
		else
		{
			CLEAR_BIT(UART0->LCRH,1);
		}
		
		/*Stop bits*/
		switch(UARTConfig->u8StopBits)
		{
			case UART_STOPBITS_1:
				CLEAR_BIT(UART0->LCRH,3);
				break;
			case UART_STOPBITS_2:
				SET_BIT(UART0->LCRH,3);
				break;
		}
		
		/*Enabled UART*/
		SET_BIT(UART0->CTL,0);

		
		/*Function to be executed when interrupt occurs*/
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_RECEIVE))
		{
			SET_BIT(UART0->IM,UART_INTERRUPTSOURCE_RECEIVE);
			UART0_vidPutISRFunction(UART_INTERRUPTSOURCE_RECEIVE,UARTConfig->ptrFHandlerReceive);
		}
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_TRANSMIT))
		{
			SET_BIT(UART0->IM,UART_INTERRUPTSOURCE_TRANSMIT);
			UART0_vidPutISRFunction(UART_INTERRUPTSOURCE_TRANSMIT,UARTConfig->ptrFHandlerTransmit);
		}
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_PARITY))
		{
			SET_BIT(UART0->IM,UART_INTERRUPTSOURCE_PARITY);
			UART0_vidPutISRFunction(UART_INTERRUPTSOURCE_PARITY,UARTConfig->ptrFHandlerParity);
		}
}

void UART0_vidPutISRFunction(u8 u8InterruptSource,void(*ptrF)(void))
{
	switch(u8InterruptSource)
	{
		case UART_INTERRUPTSOURCE_RECEIVE:
			UART0_callback = ptrF;
		break;
		case UART_INTERRUPTSOURCE_TRANSMIT:
			UART0_callback_transmit = ptrF;
		break;
		case UART_INTERRUPTSOURCE_PARITY:
			UART0_callback_parity = ptrF;
		break;
	}
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
	if(GET_BIT(UART0->MIS,4) == 1)
	{
		UART0_callback();
		SET_BIT(UART0->ICR,4);
	}
	else if (GET_BIT(UART0->MIS,5) == 1)
	{
		UART0_callback_transmit();
		SET_BIT(UART0->ICR,5);
	}
	else if(GET_BIT(UART0->MIS,8) == 1)
	{
		
		UART0_callback_parity();
		SET_BIT(UART0->ICR,8);

	}
}
#endif

#ifdef USED_UART1
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
				UART1->LCRH |= 0x0<<5;
				break;
			case UART_WORDSIZE_6:
				UART1->LCRH |= 0x1<<5;
				break;
			case UART_WORDSIZE_7:
				UART1->LCRH |= 0x2<<5;
				break;
			case UART_WORDSIZE_8:
				UART1->LCRH |= 0x3<<5; 
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
			
		/*Function to be executed when interrupt occurs*/
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_RECEIVE))
		{
			SET_BIT(UART1->IM,UART_INTERRUPTSOURCE_RECEIVE);
			UART1_vidPutISRFunction(UART_INTERRUPTSOURCE_RECEIVE,UARTConfig->ptrFHandlerReceive);
		}
		if(GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_TRANSMIT))
		{
			SET_BIT(UART1->IM,UART_INTERRUPTSOURCE_TRANSMIT);
			UART1_vidPutISRFunction(UART_INTERRUPTSOURCE_TRANSMIT,UARTConfig->ptrFHandlerTransmit);
		}
		if(GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_PARITY))
		{
			SET_BIT(UART1->IM,UART_INTERRUPTSOURCE_PARITY);
			UART1_vidPutISRFunction(UART_INTERRUPTSOURCE_PARITY,UARTConfig->ptrFHandlerParity);
		}	
}

void UART1_vidPutISRFunction(u8 u8InterruptSource,void(*ptrF)(void))
{
	switch(u8InterruptSource)
	{
		case UART_INTERRUPTSOURCE_RECEIVE:
		UART1_callback = ptrF;
		break;
		case UART_INTERRUPTSOURCE_TRANSMIT:
		UART1_callback_transmit = ptrF;
		break;
		case UART_INTERRUPTSOURCE_PARITY:
		UART1_callback_parity = ptrF;
		break;
		}
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
	if(GET_BIT(UART1->MIS,4) == 1)
	{
		UART1_callback();
		SET_BIT(UART1->ICR,4);
	}
	else if (GET_BIT(UART1->MIS,5) == 1)
	{
		UART1_callback_transmit();
		SET_BIT(UART1->ICR,5);
	}
	else if(GET_BIT(UART1->MIS,8) == 1)
	{
		UART1_callback_parity();
		SET_BIT(UART1->ICR,8);
	}
}
#endif

#ifdef USED_UART2
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
				UART2->LCRH |= 0x0<<5;
				break;
			case UART_WORDSIZE_6:
				UART2->LCRH |= 0x1<<5;
				break;
			case UART_WORDSIZE_7:
				UART2->LCRH |= 0x2<<5;
				break;
			case UART_WORDSIZE_8:
				UART2->LCRH |= 0x3<<5;
				break;
		
		}
		
		
		/*Clock divisor configuration*/
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
	
		/*Function to be executed when interrupt occurs*/
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_RECEIVE))
		{
			SET_BIT(UART2->IM,UART_INTERRUPTSOURCE_RECEIVE);
			UART2_vidPutISRFunction(UART_INTERRUPTSOURCE_RECEIVE,UARTConfig->ptrFHandlerReceive);
		}
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_TRANSMIT))
		{
			SET_BIT(UART2->IM,UART_INTERRUPTSOURCE_TRANSMIT);
			UART2_vidPutISRFunction(UART_INTERRUPTSOURCE_TRANSMIT,UARTConfig->ptrFHandlerTransmit);
		}
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_PARITY))
		{
			SET_BIT(UART2->IM,UART_INTERRUPTSOURCE_PARITY);
			UART2_vidPutISRFunction(UART_INTERRUPTSOURCE_PARITY,UARTConfig->ptrFHandlerParity);
		}	
}

void UART2_vidPutISRFunction(u8 u8InterruptSource,void(*ptrF)(void))
{
	switch(u8InterruptSource)
	{
		case UART_INTERRUPTSOURCE_RECEIVE:
		UART2_callback = ptrF;
		break;
		case UART_INTERRUPTSOURCE_TRANSMIT:
		UART2_callback_transmit = ptrF;
		break;
		case UART_INTERRUPTSOURCE_PARITY:
		UART2_callback_parity = ptrF;
		break;
		}
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
	if(GET_BIT(UART2->MIS,4) == 1)
	{
		UART2_callback();
		SET_BIT(UART2->ICR,4);
	}
	else if (GET_BIT(UART2->MIS,5) == 1)
	{
		UART2_callback_transmit();
		SET_BIT(UART2->ICR,5);
	}
	else if(GET_BIT(UART2->MIS,8) == 1)
	{
		
		UART2_callback_parity();
		SET_BIT(UART2->ICR,8);

	}
}
#endif

#ifdef USED_UART3
void UART3_vidInit(UARTConfig_t * UARTConfig)
{
	UART3->CTL = 0;         /* UART5 module disbable */
	
    UART3->IBRD = UARTConfig->u16Integer;      /* for 9600 baud rate, integer = 104 */
    UART3->FBRD = UARTConfig->u8Fraction;       /* for 9600 baud rate, fractional = 11*/
	
		/*select system clock*/
		if (UARTConfig->u8ClockSource == UART_CLOCKSOURCE_RC)
		{
			UART3->CC |= 0; 
		}
		else
		{
			UART3->CC = 0x5;
		}
		UART3->DR &= 0;
		
		if (UARTConfig->u8FIFOEnabled)
		{
			SET_BIT(UART3->LCRH,4);
		}
		else
		{
			CLEAR_BIT(UART3->LCRH,4);
		}
	
		/*Data length*/
		switch(UARTConfig->u8WordLength)
		{
			case UART_WORDSIZE_5:
				UART3->LCRH |= 0x0<<5;
				break;
			case UART_WORDSIZE_6:
				UART3->LCRH |= 0x1<<5;
				break;
			case UART_WORDSIZE_7:
				UART3->LCRH |= 0x2<<5;
				break;
			case UART_WORDSIZE_8:
				UART3->LCRH |= 0x3<<5;
				break;
		
		}
		
		if (UARTConfig->u8HighSpeedEnabled == UART_HIGHSPEED_FALSE)
		{
			CLEAR_BIT(UART3->CTL,5);
		}
		else
		{
			SET_BIT(UART3->CTL,5);

		}
		
		/*Select Rx or TX or bot to be enabled*/
		switch(UARTConfig->u8RxTx)
		{
			case UART_RXTX_BOTH:
				SET_BIT(UART3->CTL,8);
				SET_BIT(UART3->CTL,9);
				break;
			case UART_RXTX_RX_ONLY:
						SET_BIT(UART3->CTL,9);
				break;
			case UART_RXTX_TX_ONLY:
				SET_BIT(UART3->CTL,8);
			break;
		}
		
		/*Enabled UART*/
		SET_BIT(UART3->CTL,0);
	
		
		/*Function to be executed when interrupt occurs*/
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_RECEIVE))
		{
			SET_BIT(UART3->IM,UART_INTERRUPTSOURCE_RECEIVE);
			UART3_vidPutISRFunction(UART_INTERRUPTSOURCE_RECEIVE,UARTConfig->ptrFHandlerReceive);
		}
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_TRANSMIT))
		{
			SET_BIT(UART3->IM,UART_INTERRUPTSOURCE_TRANSMIT);
			UART3_vidPutISRFunction(UART_INTERRUPTSOURCE_TRANSMIT,UARTConfig->ptrFHandlerTransmit);
		}
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_PARITY))
		{
			SET_BIT(UART3->IM,UART_INTERRUPTSOURCE_PARITY);
			UART3_vidPutISRFunction(UART_INTERRUPTSOURCE_PARITY,UARTConfig->ptrFHandlerParity);
		}	
}

void UART3_vidPutISRFunction(u8 u8InterruptSource,void(*ptrF)(void))
{
	switch(u8InterruptSource)
	{
		case UART_INTERRUPTSOURCE_RECEIVE:
		UART3_callback = ptrF;
		break;
		case UART_INTERRUPTSOURCE_TRANSMIT:
		UART3_callback_transmit = ptrF;
		break;
		case UART_INTERRUPTSOURCE_PARITY:
		UART3_callback_parity = ptrF;
		break;
		}
}

void UART3_vidSendByte(unsigned char data)  
{
    while((UART3->FR & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART3->DR = data;                  /* before giving it another byte */
}

char UART3_u8GetReceivedByte(void)
{
	return (u8) UART3->DR;
}

char UART3_Receiver(void)  
{
    char data;
	  while((UART3->FR & (1<<4)) != 0); /* wait until Rx buffer is not full */
    data = (char) UART3->DR ;  	/* before giving it another byte */
    return (unsigned char) data; 
}

void UART3_vidSendString(char *str)
{
  while(*str)
	{
		UART3_vidSendByte(*(str++));
	}
}

void UART3_Handler()
{
	if(GET_BIT(UART3->MIS,4) == 1)
	{
		UART3_callback();
		SET_BIT(UART3->ICR,4);
	}
	else if (GET_BIT(UART3->MIS,5) == 1)
	{
		UART3_callback_transmit();
		SET_BIT(UART3->ICR,5);
	}
	else if(GET_BIT(UART3->MIS,8) == 1)
	{
		
		UART3_callback_parity();
		SET_BIT(UART3->ICR,8);
	}
}
#endif


/*UART4 functions*/
#ifdef USED_UART4
void UART4_vidInit(UARTConfig_t * UARTConfig)
{
		UART4->CTL = 0;         /* UART5 module disbable */
	
    UART4->IBRD = UARTConfig->u16Integer;      /* for 9600 baud rate, integer = 104 */
    UART4->FBRD = UARTConfig->u8Fraction;       /* for 9600 baud rate, fractional = 11*/
	
		/*select system clock*/
		if (UARTConfig->u8ClockSource == UART_CLOCKSOURCE_RC)
		{
			UART4->CC |= 0; 
		}
		else
		{
			UART4->CC = 0x5;
		}
		UART4->DR &= 0;
		
		if (UARTConfig->u8FIFOEnabled)
		{
			SET_BIT(UART4->LCRH,4);
		}
		else
		{
			CLEAR_BIT(UART4->LCRH,4);
		}
	
		/*Data length*/
		switch(UARTConfig->u8WordLength)
		{
			case UART_WORDSIZE_5:
				UART4->LCRH |= 0x0<<5;
				break;
			case UART_WORDSIZE_6:
				UART4->LCRH |= 0x1<<5;
				break;
			case UART_WORDSIZE_7:
				UART4->LCRH |= 0x2<<5;
				break;
			case UART_WORDSIZE_8:
				UART4->LCRH |= 0x3<<5;
				break;
		
		}
		
		if (UARTConfig->u8HighSpeedEnabled == UART_HIGHSPEED_FALSE)
		{
			CLEAR_BIT(UART4->CTL,5);
		}
		else
		{
			SET_BIT(UART4->CTL,5);

		}
		
		/*Select Rx or TX or bot to be enabled*/
		switch(UARTConfig->u8RxTx)
		{
			case UART_RXTX_BOTH:
				SET_BIT(UART4->CTL,8);
				SET_BIT(UART4->CTL,9);
				break;
			case UART_RXTX_RX_ONLY:
						SET_BIT(UART4->CTL,9);
				break;
			case UART_RXTX_TX_ONLY:
				SET_BIT(UART4->CTL,8);
			break;
		}
		
		/*Enabled UART*/
		SET_BIT(UART4->CTL,0);
	
		if (UARTConfig->u8InterruptEnabled)
		{
			/*Receive interrupt*/
			SET_BIT(UART4->IM,4);
		}
		else
		{
			CLEAR_BIT(UART4->IM,4);
		}
		
		/*Function to be executed when interrupt occurs*/
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_RECEIVE))
		{
			SET_BIT(UART4->IM,UART_INTERRUPTSOURCE_RECEIVE);
			UART4_vidPutISRFunction(UART_INTERRUPTSOURCE_RECEIVE,UARTConfig->ptrFHandlerReceive);
		}
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_TRANSMIT))
		{
			SET_BIT(UART4->IM,UART_INTERRUPTSOURCE_TRANSMIT);
			UART4_vidPutISRFunction(UART_INTERRUPTSOURCE_TRANSMIT,UARTConfig->ptrFHandlerTransmit);
		}
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_PARITY))
		{
			SET_BIT(UART4->IM,UART_INTERRUPTSOURCE_PARITY);
			UART4_vidPutISRFunction(UART_INTERRUPTSOURCE_PARITY,UARTConfig->ptrFHandlerParity);
		}	
}

void UART4_vidSendByte(unsigned char data)  
{
    while((UART4->FR & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART4->DR = data;                  /* before giving it another byte */
}

char UART4_Receiver(void)  
{
    char data;
	  while((UART4->FR & (1<<4)) != 0); /* wait until Rx buffer is not full */
    data = (char) UART4->DR ;  	/* before giving it another byte */
    return (unsigned char) data; 
}

char UART4_u8GetReceivedByte(void)
{
	return (u8) UART4->DR;
}

void UART4_vidPutISRFunction(u8 u8InterruptSource,void(*ptrF)(void))
{
	switch(u8InterruptSource)
	{
		case UART_INTERRUPTSOURCE_RECEIVE:
		UART4_callback = ptrF;
		break;
		case UART_INTERRUPTSOURCE_TRANSMIT:
		UART4_callback_transmit = ptrF;
		break;
		case UART_INTERRUPTSOURCE_PARITY:
		UART4_callback_parity = ptrF;
		break;
		}
}

void UART4_vidSendString(char *str)
{
  while(*str)
	{
		UART4_vidSendByte(*(str++));
	}
}


void UART4_Handler()
{
	if(GET_BIT(UART4->MIS,4) == 1)
	{
		UART4_callback();
		SET_BIT(UART4->ICR,4);
	}
	else if (GET_BIT(UART4->MIS,5) == 1)
	{
		UART4_callback_transmit();
		SET_BIT(UART4->ICR,5);
	}
	else if(GET_BIT(UART4->MIS,8) == 1)
	{
		UART4_callback_parity();
		SET_BIT(UART4->ICR,8);
	}
}

#endif
/*UART5*/
#ifdef USED_UART5
void UART5_vidInit(UARTConfig_t * UARTConfig)
{
		UART5->CTL = 0;         /* UART5 module disbable */
	
    UART5->IBRD = UARTConfig->u16Integer;      /* for 9600 baud rate, integer = 104 */
    UART5->FBRD = UARTConfig->u8Fraction;       /* for 9600 baud rate, fractional = 11*/
	
		/*select system clock*/
		if (UARTConfig->u8ClockSource == UART_CLOCKSOURCE_RC)
		{
			UART5->CC |= 0; 
		}
		else
		{
			UART5->CC = 0x5;
		}
		UART5->DR &= 0;
		
		if (UARTConfig->u8FIFOEnabled)
		{
			SET_BIT(UART5->LCRH,4);
		}
		else
		{
			CLEAR_BIT(UART5->LCRH,4);
		}
	
		/*Data length*/
		switch(UARTConfig->u8WordLength)
		{
			case UART_WORDSIZE_5:
				UART5->LCRH |= 0x0<<5;
				break;
			case UART_WORDSIZE_6:
				UART5->LCRH |= 0x1<<5;
				break;
			case UART_WORDSIZE_7:
				UART5->LCRH |= 0x2<<5;
				break;
			case UART_WORDSIZE_8:
				UART5->LCRH |= 0x3<<5;
				break;
		
		}
		
		if (UARTConfig->u8HighSpeedEnabled == UART_HIGHSPEED_FALSE)
		{
			CLEAR_BIT(UART5->CTL,5);
		}
		else
		{
			SET_BIT(UART5->CTL,5);

		}
		
		/*Select Rx or TX or bot to be enabled*/
		switch(UARTConfig->u8RxTx)
		{
			case UART_RXTX_BOTH:
				SET_BIT(UART5->CTL,8);
				SET_BIT(UART5->CTL,9);
				break;
			case UART_RXTX_RX_ONLY:
						SET_BIT(UART5->CTL,9);
				break;
			case UART_RXTX_TX_ONLY:
				SET_BIT(UART5->CTL,8);
			break;
		}
		
		/*Enabled UART*/
		SET_BIT(UART5->CTL,0);
	
		
		/*Function to be executed when interrupt occurs*/
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_RECEIVE))
		{
			SET_BIT(UART5->IM,UART_INTERRUPTSOURCE_RECEIVE);
			UART5_vidPutISRFunction(UART_INTERRUPTSOURCE_RECEIVE,UARTConfig->ptrFHandlerReceive);
		}
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_TRANSMIT))
		{
			SET_BIT(UART5->IM,UART_INTERRUPTSOURCE_TRANSMIT);
			UART5_vidPutISRFunction(UART_INTERRUPTSOURCE_TRANSMIT,UARTConfig->ptrFHandlerTransmit);
		}
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_PARITY))
		{
			SET_BIT(UART5->IM,UART_INTERRUPTSOURCE_PARITY);
			UART5_vidPutISRFunction(UART_INTERRUPTSOURCE_PARITY,UARTConfig->ptrFHandlerParity);
		}	
}

void UART5_vidSendByte(unsigned char data)  
{
    while((UART5->FR & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART5->DR = data;                  /* before giving it another byte */
}

char UART5_Receiver(void)  
{
    char data;
	  while((UART5->FR & (1<<4)) != 0); /* wait until Rx buffer is not full */
    data = (char) UART5->DR ;  	/* before giving it another byte */
    return (unsigned char) data; 
}

char UART5_u8GetReceivedByte(void)
{
	return (u8) UART5->DR;
}

void UART5_vidPutISRFunction(u8 u8InterruptSource,void(*ptrF)(void))
{
	switch(u8InterruptSource)
	{
		case UART_INTERRUPTSOURCE_RECEIVE:
		UART5_callback = ptrF;
		break;
		case UART_INTERRUPTSOURCE_TRANSMIT:
		UART5_callback_transmit = ptrF;
		break;
		case UART_INTERRUPTSOURCE_PARITY:
		UART5_callback_parity = ptrF;
		break;
		}
}

void UART5_vidSendString(char *str)
{
  while(*str)
	{
		UART5_vidSendByte(*(str++));
	}
}

void UART5_Handler()
{
	if(GET_BIT(UART5->MIS,4) == 1)
	{
		UART5_callback();
		SET_BIT(UART5->ICR,4);
	}
	else if (GET_BIT(UART5->MIS,5) == 1)
	{
		UART5_callback_transmit();
		SET_BIT(UART5->ICR,5);
	}
	else if(GET_BIT(UART5->MIS,8) == 1)
	{
		UART5_callback_parity();
		SET_BIT(UART5->ICR,8);
	}
}
#endif
#ifdef USED_UART6
/*UART6 function*/
void UART6_vidInit(UARTConfig_t * UARTConfig)
{
		UART6->CTL = 0;         /* UART5 module disbable */
	
    UART6->IBRD = UARTConfig->u16Integer;      /* for 9600 baud rate, integer = 104 */
    UART6->FBRD = UARTConfig->u8Fraction;       /* for 9600 baud rate, fractional = 11*/
	
		/*select system clock*/
		if (UARTConfig->u8ClockSource == UART_CLOCKSOURCE_RC)
		{
			UART6->CC |= 0; 
		}
		else
		{
			UART6->CC = 0x5;
		}
		UART6->DR &= 0;
		
		if (UARTConfig->u8FIFOEnabled)
		{
			SET_BIT(UART6->LCRH,4);
		}
		else
		{
			CLEAR_BIT(UART6->LCRH,4);
		}
	
		/*Data length*/
		switch(UARTConfig->u8WordLength)
		{
			case UART_WORDSIZE_5:
				UART6->LCRH |= 0x0<<5;
				break;
			case UART_WORDSIZE_6:
				UART6->LCRH |= 0x1<<5;
				break;
			case UART_WORDSIZE_7:
				UART6->LCRH |= 0x2<<5;
				break;
			case UART_WORDSIZE_8:
				UART6->LCRH |= 0x3<<5;     /* data lenght 8-bit, not parity bit, no FIFO */
				break;
		
		}
		
		if (UARTConfig->u8HighSpeedEnabled == UART_HIGHSPEED_FALSE)
		{
			CLEAR_BIT(UART6->CTL,5);
		}
		else
		{
			SET_BIT(UART6->CTL,5);

		}
		
		/*Select Rx or TX or bot to be enabled*/
		switch(UARTConfig->u8RxTx)
		{
			case UART_RXTX_BOTH:
				SET_BIT(UART6->CTL,8);
				SET_BIT(UART6->CTL,9);
				break;
			case UART_RXTX_RX_ONLY:
						SET_BIT(UART6->CTL,9);
				break;
			case UART_RXTX_TX_ONLY:
				SET_BIT(UART6->CTL,8);
			break;
		}
		
		/*Enabled UART*/
		SET_BIT(UART6->CTL,0);
	
		if (UARTConfig->u8InterruptEnabled)
		{
			/*Receive interrupt*/
			SET_BIT(UART6->IM,4);
		}
		else
		{
			CLEAR_BIT(UART6->IM,4);
		}
		
		/*Function to be executed when interrupt occurs*/
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_RECEIVE))
		{
			SET_BIT(UART6->IM,UART_INTERRUPTSOURCE_RECEIVE);
			UART6_vidPutISRFunction(UART_INTERRUPTSOURCE_RECEIVE,UARTConfig->ptrFHandlerReceive);
		}
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_TRANSMIT))
		{
			SET_BIT(UART6->IM,UART_INTERRUPTSOURCE_TRANSMIT);
			UART6_vidPutISRFunction(UART_INTERRUPTSOURCE_TRANSMIT,UARTConfig->ptrFHandlerTransmit);
		}
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_PARITY))
		{
			SET_BIT(UART6->IM,UART_INTERRUPTSOURCE_PARITY);
			UART6_vidPutISRFunction(UART_INTERRUPTSOURCE_PARITY,UARTConfig->ptrFHandlerParity);
		}	
}

void UART6_vidSendByte(unsigned char data)  
{
    while((UART6->FR & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART6->DR = data;                  /* before giving it another byte */
}

char UART6_Receiver(void)  
{
    char data;
	  while((UART6->FR & (1<<4)) != 0); /* wait until Rx buffer is not full */
    data = (char) UART6->DR ;  	/* before giving it another byte */
    return (unsigned char) data; 
}

char UART6_u8GetReceivedByte(void)
{
	return (u8) UART6->DR;
}

void UART6_vidPutISRFunction(u8 u8InterruptSource,void(*ptrF)(void))
{
	switch(u8InterruptSource)
	{
		case UART_INTERRUPTSOURCE_RECEIVE:
		UART6_callback = ptrF;
		break;
		case UART_INTERRUPTSOURCE_TRANSMIT:
		UART6_callback_transmit = ptrF;
		break;
		case UART_INTERRUPTSOURCE_PARITY:
		UART6_callback_parity = ptrF;
		break;
	}
}

void UART6_vidSendString(char *str)
{
  while(*str)
	{
		UART6_vidSendByte(*(str++));
	}
}


void UART6_Handler()
{
	if(GET_BIT(UART6->MIS,4) == 1)
	{
		UART6_callback();
		SET_BIT(UART6->ICR,4);
	}
	else if (GET_BIT(UART6->MIS,5) == 1)
	{
		UART6_callback_transmit();
		SET_BIT(UART6->ICR,5);
	}
	else if(GET_BIT(UART6->MIS,8) == 1)
	{
		UART6_callback_parity();
		SET_BIT(UART6->ICR,8);
	}
}
#endif

#ifdef USED_UART7
/*UART7 functions*/
void UART7_vidInit(UARTConfig_t * UARTConfig)
{
		UART7->CTL = 0;         /* UART5 module disbable */
	
    UART7->IBRD = UARTConfig->u16Integer;      /* for 9600 baud rate, integer = 104 */
    UART7->FBRD = UARTConfig->u8Fraction;       /* for 9600 baud rate, fractional = 11*/
	
		/*select system clock*/
		if (UARTConfig->u8ClockSource == UART_CLOCKSOURCE_RC)
		{
			UART7->CC |= 0; 
		}
		else
		{
			UART7->CC = 0x5;
		}
		UART7->DR &= 0;
		
		if (UARTConfig->u8FIFOEnabled)
		{
			SET_BIT(UART7->LCRH,4);
		}
		else
		{
			CLEAR_BIT(UART7->LCRH,4);
		}
	
		/*Data length*/
		switch(UARTConfig->u8WordLength)
		{
			case UART_WORDSIZE_5:
				UART7->LCRH |= 0x0<<5;
				break;
			case UART_WORDSIZE_6:
				UART7->LCRH |= 0x1<<5;
				break;
			case UART_WORDSIZE_7:
				UART7->LCRH |= 0x2<<5;
				break;
			case UART_WORDSIZE_8:
				UART7->LCRH |= 0x3<<5;     /* data lenght 8-bit, not parity bit, no FIFO */
				break;
		
		}
		
		if (UARTConfig->u8HighSpeedEnabled == UART_HIGHSPEED_FALSE)
		{
			CLEAR_BIT(UART7->CTL,5);
		}
		else
		{
			SET_BIT(UART7->CTL,5);

		}
		
		/*Select Rx or TX or bot to be enabled*/
		switch(UARTConfig->u8RxTx)
		{
			case UART_RXTX_BOTH:
				SET_BIT(UART7->CTL,8);
				SET_BIT(UART7->CTL,9);
				break;
			case UART_RXTX_RX_ONLY:
						SET_BIT(UART7->CTL,9);
				break;
			case UART_RXTX_TX_ONLY:
				SET_BIT(UART7->CTL,8);
			break;
		}
		
		/*Enabled UART*/
		SET_BIT(UART7->CTL,0);
		
		/*Function to be executed when interrupt occurs*/
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_RECEIVE))
		{
			SET_BIT(UART7->IM,UART_INTERRUPTSOURCE_RECEIVE);
			UART7_vidPutISRFunction(UART_INTERRUPTSOURCE_RECEIVE,UARTConfig->ptrFHandlerReceive);
		}
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_TRANSMIT))
		{
			SET_BIT(UART7->IM,UART_INTERRUPTSOURCE_TRANSMIT);
			UART7_vidPutISRFunction(UART_INTERRUPTSOURCE_TRANSMIT,UARTConfig->ptrFHandlerTransmit);
		}
		if (GET_BIT(UARTConfig->u8InterruptEnabled,UART_INTERRUPTSOURCE_PARITY))
		{
			SET_BIT(UART7->IM,UART_INTERRUPTSOURCE_PARITY);
			UART7_vidPutISRFunction(UART_INTERRUPTSOURCE_PARITY,UARTConfig->ptrFHandlerParity);
		}	
}

void UART7_vidSendByte(unsigned char data)  
{
    while((UART7->FR & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART7->DR = data;                  /* before giving it another byte */
}

char UART7_Receiver(void)  
{
    char data;
	  while((UART7->FR & (1<<4)) != 0); /* wait until Rx buffer is not full */
    data = (char) UART7->DR ;  	/* before giving it another byte */
    return (unsigned char) data; 
}

char UART7_u8GetReceivedByte(void)
{
	return (u8) UART7->DR;
}

void UART7_vidPutISRFunction(u8 u8InterruptSource,void(*ptrF)(void))
{
	switch(u8InterruptSource)
	{
		case UART_INTERRUPTSOURCE_RECEIVE:
		UART7_callback = ptrF;
		break;
		case UART_INTERRUPTSOURCE_TRANSMIT:
		UART7_callback_transmit = ptrF;
		break;
		case UART_INTERRUPTSOURCE_PARITY:
		UART7_callback_parity = ptrF;
		break;
	}
}

void UART7_vidSendString(char *str)
{
  while(*str)
	{
		UART7_vidSendByte(*(str++));
	}
}


void UART7_Handler()
{
	if(GET_BIT(UART7->MIS,4) == 1)
	{
		UART7_callback();
		SET_BIT(UART7->ICR,4);
	}
	else if (GET_BIT(UART7->MIS,5) == 1)
	{
		UART7_callback_transmit();
		SET_BIT(UART7->ICR,5);
	}
	else if(GET_BIT(UART7->MIS,8) == 1)
	{
		UART7_callback_parity();
		SET_BIT(UART7->ICR,8);
	}
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
#endif
