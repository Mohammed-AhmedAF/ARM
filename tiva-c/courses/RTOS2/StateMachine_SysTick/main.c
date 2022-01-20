#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "SysTick_interface.h"
#include "UART_interface.h"

enum states
{
	STATE_A = 0,
	STATE_B,
	STATE_C
};

typedef enum states states_t;

void vidStateMachineInit(void);
void state_a_function(void);
void state_b_function(void);
void state_c_function(void);




static void (*state_table[3]) (void) = {state_a_function, state_b_function, state_c_function};

static states_t current_state;
static u32 clock;

void vidStateMachineInit(void)
{
	current_state = STATE_A;
	clock = 0;
}

void vidStateSwitcher(void)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);
		state_table[current_state]();
	clock++;
	if (clock == 10)
	{
		clock = 0;
	}
}

int main(void)
{
	/*Enabling clock for peripherals*/
	SYSCNTRL_vidChangeSysClock(SYSCNTRL_SYSCLOCK_16MHZ);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	
	/*UART GPIO pin configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	
	/*LED*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_GREEN,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DEN_SET);
	
	/*UART configuation*/
	UARTConfig_t stUART0Config;
	stUART0Config.u16Integer = 8;
	stUART0Config.u8Fraction = 44;
	stUART0Config.u8FIFOEnabled = UART_FIFO_DISABLED;
	stUART0Config.u8HighSpeedEnabled = UART_HIGHSPEED_DIV16;
	stUART0Config.u8InterruptEnabled = UART_INTERRUPT_DISABLED;
	stUART0Config.u8RxTx = UART_RXTX_BOTH;
	stUART0Config.u8WordLength = UART_WORDSIZE_8;
	stUART0Config.u8ClockSource = UART_CLOCKSOURCE_RC;
	
	/*UART initialization*/
	UART0_vidInit(&stUART0Config);

	vidStateMachineInit();

	/*SysTickConfiguration*/
	SysTickConfig_t stSysTickConfig;
	stSysTickConfig.u32ReloadValue = 16000000;
	stSysTickConfig.u8ClockSource = SYSTICK_SYSTEM_CLOCK;
	stSysTickConfig.u8Interrupt = SYSTICK_INTERRUPT_ENABLED;
	stSysTickConfig.ptrFunc = vidStateSwitcher;
	SysTick_vidInitExtended(&stSysTickConfig);
	SysTick_vidStart();
	
	
	while(1);
}

void state_a_function(void)
{
	if (clock == 2)
	{
		current_state = STATE_B;
		UART0_vidSendString("This is the execution of state A.\r\n");
	}
}

void state_b_function(void)
{
	if (clock == 5)
	{
		current_state = STATE_C;
		UART0_vidSendString("This is the execution of state B.\r\n");
	}
}

void state_c_function(void)
{
	if (clock == 9)
	{
		current_state = STATE_A;
		UART0_vidSendString("This is the execution of state C.\r\n");

	}
}