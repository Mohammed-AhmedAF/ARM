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

void SYSCNTRL_vidEnableTimerClock(u8 u8TimerID)
{
	switch(u8TimerID)
	{
		case SYSCNTRL_TIMER_0:
			SET_BIT(RCGCTIMER,0);
		break;
	}
}

void SYSCNTL_vidUsePLL(void)
{
	/*Set BYPASS bit*/
	SET_BIT(RCC,11);
	/*Clearing USESYS*/
	CLEAR_BIT(RCC,22);
	
	/*Select XTAL*/
	RCC |= (0x15<<6);
	
	/*Select OSC*/
	CLEAR_BIT(RCC,4);
	CLEAR_BIT(RCC,5);
	
	/*Clear PWRDN*/
	CLEAR_BIT(RCC,13);
	
	/*Desired clock divisor (0x04)*/
	CLEAR_BIT(RCC,23);
	CLEAR_BIT(RCC,24);
	SET_BIT(RCC,25);
	CLEAR_BIT(RCC,26);
	
	/*SET USESYS*/
	SET_BIT(RCC,22);
	
	/*wait for PLL to lock*/
	while(GET_BIT(RIS,6) == 0);
	
	/*Last step: Enabling PLL by clearing BYPASS*/
	CLEAR_BIT(RCC,11);

}

void SYSCNTRL_vidPLL80(void)
{
	// 1. Enable USERCC2 in RCC2
    RCC2 |= 0x80000000; // RCC2[31]=USERCC2
    // 2. Bypass PLL while initializing
    RCC2 |= 0x00000800; // RCC2[11]=BYPASS2
    // 3. Set external crystal value and oscillator source for PLL
    RCC = (RCC & ~0x000007C0) //Clear RCC[10:6]=XTAL
                  + (0x15 << 6);              // 16MHz extern xtal
    RCC2 &= ~0x00000070;              // RCC2[6:4]=OSCSRC2 000=Main Oscillator
    // 4. Clearning PWRDN to active PLL
    // RCC2[13]=PWRDN 0:The PLL operate normally
    RCC2 &= ~0x00002000;           
    // 5. Set system clock
    // RCC2[30]=DIV400 Select 400MHz(from PLL)
    RCC2 |= 0x40000000;            
    //RCC2[28:21]=SYSDIV2 400MHz/(4+1) = 80MHz
    RCC2 = (RCC2 & ~0x1FC00000) + (0x04 << 22);
    // 6. Wait for PLL to lock by polling PLLLRIS
    while( (RIS & 0x00000040) == 0) {};
    // 7. Set BYPASS to 0, select PLL as the source of system clock
    RCC2 &= ~0x00000800;
}