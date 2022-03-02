#include "STD_TYPES.h"
#include "TM4C123.h" // Device header
#include "Macros.h"
#include "SYSCNTRL_private.h"
#include "SYSCNTRL_interface.h"

void SYSCNTRL_vidEnableGPIOClock(u8 u8PortNumber)
{
	switch (u8PortNumber)
	{
	case SYSCNTRL_GPIO_PORTA:
		SET_BIT(RCGCGPIO, 0);
		break;
	case SYSCNTRL_GPIO_PORTB:
		SET_BIT(RCGCGPIO, 1);
		break;
	case SYSCNTRL_GPIO_PORTC:
		SET_BIT(RCGCGPIO, 2);
		break;
	case SYSCNTRL_GPIO_PORTD:
		SET_BIT(RCGCGPIO, 3);
		break;
	case SYSCNTRL_GPIO_PORTE:
		SET_BIT(RCGCGPIO, 4);
		break;
	case SYSCNTRL_GPIO_PORTF:
		SET_BIT(RCGCGPIO, 5);
		break;
	}
}

void SYSCNTRL_vidEnableUARTClock(u8 u8UARTChannel)
{
	switch (u8UARTChannel)
	{
	case SYSCNTRL_UART0:
		SET_BIT(RCGCUART, 0);
		break;
	case SYSCNTRL_UART1:
		SET_BIT(RCGCUART, 1);
		break;
	case SYSCNTRL_UART2:
		SET_BIT(RCGCUART, 2);
		break;
	}
}

void SYSCNTRL_vidEnablePWMClock(u8 u8Module)
{
	switch(u8Module)
	{
		case SYSCNTRL_PWM_0:
				SET_BIT(RCGCPWM,0);
			break;
		case SYSCNTRL_PWM_1:
				SET_BIT(RCGCPWM,1);
			break;
	}
}

void SYSCNTRL_vidEnableSPIClock(u8 u8SPIChannel)
{
	switch(u8SPIChannel)
	{
		case SYSCNTRL_SPI0:
				SET_BIT(RCGCSSI,0);
			break;
		case SYSCNTRL_SPI1:
				SET_BIT(RCGCSSI,1);
			break;
		case SYSCNTRL_SPI2:
				SET_BIT(RCGCSSI,2);
			break;
		case SYSCNTRL_SPI3:
				SET_BIT(RCGCSSI,3);
			break;
	}
}

void SYSCNTRL_vidEnableI2CClock(u8 u8I2CPeriph)
{
	switch(u8I2CPeriph)
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

void SYSCNTRL_vidEnableADCClock(u8 u8ADCPeriph)
{
	switch (u8ADCPeriph)
	{
	case SYSCNTRL_ADC_0:
		SET_BIT(RCGCADC, 0);
		break;
	case SYSCNTRL_ADC_1:
		SET_BIT(RCGCADC, 1);
		break;
	}
}

void SYSCNTRL_vidEnableTimerClock(u8 u8Timer)
{
	switch (u8Timer)
	{
	case SYSCNTRL_TIMER_0:
		SET_BIT(RCGCTIMER,0);
		break;
	case SYSCNTRL_TIMER_1:
		SET_BIT(RCGCTIMER,1);
		break;
	case SYSCNTRL_TIMER_2:
		SET_BIT(RCGCTIMER,2);
		break;
	case SYSCNTRL_TIMER_3:
		SET_BIT(RCGCTIMER,3);
		break;
	}
}

void SYSCNTRL_vidSelectGPIOBus(u8 u8GPIOPort, u8 u8Bus)
{
	switch (u8GPIOPort)
	{
	case SYSCNTRL_GPIO_PORTA:
		if (u8Bus == SYSCNTRL_BUS_AHB)
		{
			SET_BIT(GPIOHBCTL, 0);
		}
		else
		{
			CLEAR_BIT(GPIOHBCTL, 0);
		}
		break;
	case SYSCNTRL_GPIO_PORTB:
		if (u8Bus == SYSCNTRL_BUS_AHB)
		{
			SET_BIT(GPIOHBCTL, 1);
		}
		else
		{
			CLEAR_BIT(GPIOHBCTL, 1);
		}
		break;
	case SYSCNTRL_GPIO_PORTC:
		if (u8Bus == SYSCNTRL_BUS_AHB)
		{
			SET_BIT(GPIOHBCTL, 2);
		}
		else
		{
			CLEAR_BIT(GPIOHBCTL, 2);
		}
		break;
	case SYSCNTRL_GPIO_PORTD:
		if (u8Bus == SYSCNTRL_BUS_AHB)
		{
			SET_BIT(GPIOHBCTL, 3);
		}
		else
		{
			CLEAR_BIT(GPIOHBCTL, 3);
		}
		break;
	case SYSCNTRL_GPIO_PORTE:
		if (u8Bus == SYSCNTRL_BUS_AHB)
		{
			SET_BIT(GPIOHBCTL, 4);
		}
		else
		{
			CLEAR_BIT(GPIOHBCTL, 4);
		}
		break;
	case SYSCNTRL_GPIO_PORTF:
		if (u8Bus == SYSCNTRL_BUS_AHB)
		{
			SET_BIT(GPIOHBCTL, 5);
		}
		else
		{
			CLEAR_BIT(GPIOHBCTL, 5);
		}
		break;
	}
}

void SYSCNTRL_vidChangeSysClock(u8 u8SysClock)
{
	// 1. Enable USERCC2 in RCC2
	SYSCTL->RCC2 |= 0x80000000; // RCC2[31]=USERCC2
	// 2. Bypass PLL while initializing
	SYSCTL->RCC2 |= 0x00000800; // RCC2[11]=BYPASS2
	// 3. Set external crystal value and oscillator source for PLL
	SYSCTL->RCC = (SYSCTL->RCC & ~0x000007C0) //Clear RCC[10:6]=XTAL
				  + (0x15 << 6);			  // 16MHz extern xtal
	SYSCTL->RCC2 &= ~0x00000070;			  // RCC2[6:4]=OSCSRC2 000=Main Oscillator
	// 4. Clearning PWRDN to active PLL
	// RCC2[13]=PWRDN 0:The PLL operate normally
	SYSCTL->RCC2 &= ~0x00002000;
	// 5. Set system clock
	// RCC2[30]=DIV400 Select 400MHz(from PLL)
	SYSCTL->RCC2 |= 0x40000000;
	//RCC2[28:21]=SYSDIV2 400MHz/(4+1) = 80MHz
	switch (u8SysClock)
	{
		case SYSCNTRL_SYSCLOCK_8MHZ:
		SYSCTL->RCC2 = (SYSCTL->RCC2 & ~0x1FC00000) + (0x32 << 22);
		break;
	case SYSCNTRL_SYSCLOCK_10MHZ:
		SYSCTL->RCC2 = (SYSCTL->RCC2 & ~0x1FC00000) + (0x27 << 22);
		break;
	case SYSCNTRL_SYSCLOCK_16MHZ:
		SYSCTL->RCC2 = (SYSCTL->RCC2 & ~0x1FC00000) + (0x18 << 22);
		break;
	case SYSCNTRL_SYSCLOCK_20MHZ:
		SYSCTL->RCC2 = (SYSCTL->RCC2 & ~0x1FC00000) + (0x13 << 22);
		break;
	case SYSCNTRL_SYSCLOCK_25MHZ:
		SYSCTL->RCC2 = (SYSCTL->RCC2 & ~0x1FC00000) + (0x0F << 22);
		break;
	case SYSCNTRL_SYSCLOCK_40MHZ:
		SYSCTL->RCC2 = (SYSCTL->RCC2 & ~0x1FC00000) + (0x09 << 22);
		break;
	case SYSCNTRL_SYSCLOCK_50MHZ:
		SYSCTL->RCC2 = (SYSCTL->RCC2 & ~0x1FC00000) + (0x07 << 22);
		break;
	case SYSCNTRL_SYSCLOCK_80MHZ:
		SYSCTL->RCC2 = (SYSCTL->RCC2 & ~0x1FC00000) + (0x04 << 22);
		break;
	}
	// 6. Wait for PLL to lock by polling PLLLRIS
	while ((SYSCTL->RIS & 0x00000040) == 0)
	{
	};
	// 7. Set BYPASS to 0, select PLL as the source of system clock
	SYSCTL->RCC2 &= ~0x00000800;
}
