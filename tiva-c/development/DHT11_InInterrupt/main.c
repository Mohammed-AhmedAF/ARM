#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SysTick_interface.h"
#include "SYSCNTRL_interface.h"
#include "TIMER0_interface.h"
#include "DHT11_interface.h"
#include "LCD_interface.h"
#include "UART_interface.h"
#include "APP_interface.h"
#include "SCB_interface.h"
#include "NVIC_interface.h"
#include "TM4C123.h"                    // Device header

void vidTest(void);
void vidBlink(void);
void vidProcessCommand(void);

volatile u8 u8SysTickOVFCount = 0;
volatile u8 u8ScanFlag = 0;
void vidTest(void)
{
u8SysTickOVFCount++;
	
	if (u8SysTickOVFCount == 4)
	{
		u8SysTickOVFCount = 0;
		/*PendSV interrupt set to pending*/
		SCB_vidTriggerPendSV();
	}
}
u8 ptrU8DataArr[6];

void vidProcessCommand(void)
{
 static u8 u8Command;
	u8Command = UART0_u8GetReceivedByte();
	if (u8Command == 'g')
	{
				GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_BLUE);

				APP_vidGetTemperature();

	}
}

int main(void)
{
	SYSCNTRL_vidChangeSysClock(SYSCNTRL_SYSCLOCK_16MHZ);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	
	TIMER0_vidInit(31,0);
	
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);

	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_OUTPUT);
	
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
	
	NVIC_SetPriority(PendSV_IRQn,5);
	NVIC_SetPriority(SysTick_IRQn,6);
	if (NVIC_GetPriority(PendSV_IRQn) == 4)
	{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_BLUE);
	}

	__enable_irq();
	
	SCB_vidPutISR(SCB_INTERRUPT_PENDSV,vidBlink);
	
	UARTConfig_t uart0Config;
	uart0Config.u16Integer = 8;
	uart0Config.u8Fraction = 44;
	uart0Config.ptrF = vidProcessCommand;
	uart0Config.u8HighSpeedEnabled = UART_HIGHSPEED_DIV_16;
	uart0Config.u8InterruptEnabled = UART_INTERRUPT_ENABLED;
	uart0Config.u8RxTx = UART_RXTX_BOTH;
	uart0Config.u8WordLength = UART_WORDSIZE_8;
	uart0Config.u8ClockSource = UART_CLOCKSOURCE_RC;
	UART0_vidInit(&uart0Config);
	

	
	SysTickConfig_t sysConfig;
	sysConfig.ptrFunc = vidTest;
	sysConfig.u32ReloadValue = 16000000;
	sysConfig.u8ClockSource = SYSTICK_SYSTEM_CLOCK;
	sysConfig.u8Interrupt = SYSTICK_INTERRUPT_ENABLED;
	SysTick_vidInitExtended(&sysConfig);
	//SysTick_vidStart();
	DHT11_vidInit();
	
	NVIC_EnableIRQ(NVIC_UART0);
	/*UART interrupt priority*/
	NVIC_SetPriority(NVIC_UART0,1);
	/*Timer Interrupt*/
	NVIC_SetPriority(19,0);

	u8 u8ReadingNumber = 0;
	while(1)
	{
			//UART0_vidSendString("Reading No. ");
				//UART_vidSendNumber(UART0_vidSendByte,u8ReadingNumber);
				//UART0_vidSendByte('\r');
			//UART0_vidSendByte('\n');
			//APP_vidGetTemperature();
			//TIMER0_vidDelayMicro(350000);

			//u8ReadingNumber++;
		
	}
}

 void vidBlink(void)
 {
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_RED);
 }