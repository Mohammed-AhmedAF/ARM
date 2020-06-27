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
	}
}

void SYSCNTRL_vidEnableI2CClock(u8 u8I2CModule)
{
	switch(u8I2CModule)
	{
		case SYSCNTRL_I2C_0:
			SET_BIT(RCGCI2C,0);
			break;
		case SYSCNTRL_I2C_1:
			SET_BIT(RCGCI2C,1);
			break;
		case SYSCNTRL_I2C_2:
			SET_BIT(RCGCI2C,2);
			break;
		case SYSCNTRL_I2C_3:
			SET_BIT(RCGCI2C,3);
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