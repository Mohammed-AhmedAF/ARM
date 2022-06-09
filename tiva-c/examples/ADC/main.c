#include "Macros.h"
#include "STD_TYPES.h"
#include "SYSCNTRL_interface.h"
#include "GPIO_interface.h"
#include "SysTick_interface.h"
#include "UART_interface.h"
#include "ADC_interface.h"
#include "TM4C123.h"                    // Device header
#include <stdio.h>


/*Function definition*/
void vidBlink(void);
void vidProcessCommands0(void);


/*Global variables*/
volatile u8 u8Command0;
volatile u8 u8Command1;
volatile u16 u16Count;
char mesg[12];
float voltage;
extern u32 u32ADCResult;

void (*ptrF) (u8) = (void (*) (u8)) UART0_vidSendByte;

void vidBlink(void)
{
	voltage = (u32ADCResult * 0.0008);
	UART0_vidSendByte('\n');
	UART0_vidSendByte('\r');
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN3);
	UART_vidSendNumber(ptrF,(u16)u32ADCResult);

}

void vidProcessCommands0(void)
{
	u8Command0 = UART0_u8GetReceivedByte();

	if (u8Command0 == 'a')
	{
			GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN3);

	}
	else if (u8Command0 == 'r')
	{
		u16Count = 0;
	}

}


int main(void)
{
	/*Enabling clock for used peripherals*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTE);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	SYSCNTRL_vidEnableADCClock(SYSCNTRL_ADC_1);

	/*Initializing GPIO*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);
	
	/*Initializing UART*/
	UARTConfig_t uart0Config;
	uart0Config.u8ClockSource = UART_CLOCKSOURCE_RC;
	uart0Config.u8WordLength = UART_WORDSIZE_8;
	uart0Config.u16Integer = 104;
	uart0Config.u8Fraction = 11;
	uart0Config.u8FIFOEnabled = UART_FIFO_DISABLED;
	uart0Config.u8RxTx = UART_RXTX_BOTH;
	uart0Config.u8HighSpeedEnabled = UART_HIGHSPEED_DIV16;
	uart0Config.u8InterruptEnabled = UART_INTERRUPT_ENABLED;
	
	UART0_vidInit(&uart0Config);
	UART0_vidPutISRFunction(vidProcessCommands0);
	
	/*UART0 pins configuration*/
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidConfigAnalogFunction(GPIO_PORTA,GPIO_PIN0,GPIO_ANALOG_CLEAR);
	GPIO_vidConfigAnalogFunction(GPIO_PORTA,GPIO_PIN1,GPIO_ANALOG_CLEAR);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x1);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN1,0x1);
	
	/*ADC Pin configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTE,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTE,GPIO_PIN1,GPIO_DEN_CLEAR);
	GPIO_vidConfigAnalogFunction(GPIO_PORTE,GPIO_PIN1,GPIO_ANALOG_SET);
	
	/*ADC peripheral configuration*/
	ADC_Config_t ADC1Config;
	ADC1Config.u8Sequencer = ADC_SEQUENCER_3;
	ADC1Config.u8AnalogInput = ADC_ANALOGINPUT_2;
	ADC1Config.u8InterrupEnabled = ADC_INTERRUPT_ENABLED;
	ADC1Config.u8EventTrigger = ADC_EVENT_TRIGGER_CONTINUOUS;
	
	/*ADC peipheral intialization*/
	ADC1_vidInit(&ADC1Config);
	
	/*Initializing SYSTICK*/
	SysTick_vidInit(SYSTICK_SYSTEM_CLOCK,SYSTICK_INTERRUPT_ENABLED);
	SysTick_vidPutISR(vidBlink);
	SysTick_vidSetValue(16000000);
	SysTick_vidStart();
	
	/*Enabling Interrupt*/
	/*UART0 interrupt*/
	NVIC->ISER[0] |= (1<<5);
	NVIC->IP[5] = (3<<5);
	
	
	/*ADC interrupt*/
	NVIC->ISER[1] |= (1<<19);

	__enable_irq();
	
	while(1);
	
}