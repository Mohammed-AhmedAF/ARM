#include "STD_TYPES.h"
#include "Macros.h"
#include "SYSCNTRL_private.h"
#include "SYSCNTRL_interface.h"

void SYSCNTRL_vidEnableGPIOClock(u8 u8PortNumber)
{
	switch(u8PortNumber)
	{
		case SYSCNTRL_GPIO_PORTA:
			SET_BIT(RCGCGPIO,0);
		break;
		case SYSCNTRL_GPIO_PORTB:
			SET_BIT(RCGCGPIO,1);
		break;
		case SYSCNTRL_GPIO_PORTC:
			SET_BIT(RCGCGPIO,2);
		break;
		case SYSCNTRL_GPIO_PORTD:
			SET_BIT(RCGCGPIO,3);
		break;
		case SYSCNTRL_GPIO_PORTE:
			SET_BIT(RCGCGPIO,4);
		break;
		case SYSCNTRL_GPIO_PORTF:
			SET_BIT(RCGCGPIO,5);
		break;
	}
}

void SYSCNTRL_vidEnableUARTClock(u8 u8UARTChannel)
{
	switch (u8UARTChannel)
	{
		case SYSCNTRL_UART0:
			SET_BIT(RCGCUART,0);
		break;
		case SYSCNTRL_UART1:
			SET_BIT(RCGCUART,1);
		break;
		case SYSCNTRL_UART2:
			SET_BIT(RCGCUART,2);
		break;
	}

}

void SYSCNTRL_vidEnableADCClock(u8 u8ADCPeriph)
{
	switch(u8ADCPeriph)
	{
		case SYSCNTRL_ADC_0:
			SET_BIT(RCGCADC,0);
			break;
		case SYSCNTRL_ADC_1:
			SET_BIT(RCGCADC,1);
			break;
	}
	
}

void SYSCNTRL_vidEnableTimerClock(u8 u8Timer)
{
	switch(u8Timer)
	{
		case SYSCNTRL_TIMER_0:
			SET_BIT(RCGCTIMER,0);
		break;
	}
}

void SYSCNTRL_vidSelectGPIOBus(u8 u8GPIOPort,u8 u8Bus)
{
	switch(u8GPIOPort)
	{
		case SYSCNTRL_GPIO_PORTA:
			if (u8Bus == SYSCNTRL_BUS_AHP)
			{
				SET_BIT(GPIOHBCTL,0);
			}
			else
			{
				CLEAR_BIT(GPIOHBCTL,0);
			}
			break;
		case SYSCNTRL_GPIO_PORTB:
			if (u8Bus == SYSCNTRL_BUS_AHP)
			{
				SET_BIT(GPIOHBCTL,1);
			}
			else
			{
				CLEAR_BIT(GPIOHBCTL,1);
			}
			break;
		case SYSCNTRL_GPIO_PORTC:
			if (u8Bus == SYSCNTRL_BUS_AHP)
			{
				SET_BIT(GPIOHBCTL,2);
			}
			else
			{
				CLEAR_BIT(GPIOHBCTL,2);
			}
			break;
		case SYSCNTRL_GPIO_PORTD:
			if (u8Bus == SYSCNTRL_BUS_AHP)
			{
				SET_BIT(GPIOHBCTL,3);
			}
			else
			{
				CLEAR_BIT(GPIOHBCTL,3);
			}
			break;
		case SYSCNTRL_GPIO_PORTE:
			if (u8Bus == SYSCNTRL_BUS_AHP)
			{
				SET_BIT(GPIOHBCTL,4);
			}
			else
			{
				CLEAR_BIT(GPIOHBCTL,4);
			}
			break;
		case SYSCNTRL_GPIO_PORTF:
			if (u8Bus == SYSCNTRL_BUS_AHP)
			{
				SET_BIT(GPIOHBCTL,5);
			}
			else
			{
				CLEAR_BIT(GPIOHBCTL,5);
			}
			break;
	}
}


