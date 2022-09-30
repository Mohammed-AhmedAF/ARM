#include "STD_TYPES.h"
#include "Macros.h"
#include "SysTick_interface.h"
#include "SYSCNTRL_interface.h"
#include "GPIO_interface.h"
#include "TIMER_IF_INTERFACE.h"
#include "TIMER0_interface.h"
#include "UART_interface.h"
#include "DHT11_interface.h"

void vidSysTickISR(void);
void APP_vidGetTemperature(void);

int main(void)
{
	/*Enabling running clock for peripherals*/
	SYSCNTRL_vidChangeSysClock(SYSCNTRL_SYSCLOCK_16MHZ);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	SYSCNTRL_vidEnableTimerClock(SYSCNTRL_TIMER_0);
	
	/*LED GPIO Configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);
	GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN3,STD_LOW);
	
	/*UART GPIO configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x01);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN1,0x01);

	/*UART0 peripheral configuration*/
	UARTConfig_t strctUART0Config;
	strctUART0Config.u8Module = UART_MODULE_0;
	strctUART0Config.u8ClockSource = UART_CLOCKSOURCE_RC;
	strctUART0Config.u8FIFOEnabled = UART_FIFO_DISABLED;
	strctUART0Config.u8Loopback = UART_LOOPBACK_DISABLED;
	strctUART0Config.u8WordLength = UART_WORDSIZE_8;
	strctUART0Config.u8RxTx = UART_RXTX_BOTH;
	strctUART0Config.u8HighSpeedEnabled = UART_HIGHSPEED_DIV8;
	strctUART0Config.u8InterruptEnabled = UART_INTERRUPT_DISABLED;
	strctUART0Config.u8ParityEnable = UART_PARITY_DISABLED;
	strctUART0Config.u8StopBits = UART_STOPBITS_1;
	strctUART0Config.u16Integer = 208;
	strctUART0Config.u8Fraction = 21;
	UART0_vidInit(&strctUART0Config);
	
	/*SysTick configuration*/
	SysTickConfig_t strctSysTickConfig;
	strctSysTickConfig.ptrFunc = vidSysTickISR;
	strctSysTickConfig.u32ReloadValue = 16000000;
	strctSysTickConfig.u8ClockSource = SYSTICK_CLOCK_SYSTEM;
	strctSysTickConfig.u8Interrupt = SYSTICK_INTERRUPT_ENABLED;
	SysTick_vidInitExtended(&strctSysTickConfig);
	SysTick_vidStart();
	
	TIMERHandle_t timer0Handle;
	timer0Handle.ptrFDisableTimer = TIMER0_vidDisableTimer;
	timer0Handle.ptrFDelayMicro = TIMER0_vidDelayMirco;
	timer0Handle.ptrFDelayMilli = TIMER0_vidDelayMilli;
	
	/*DHT11 configuration*/
	DHT11_vidInit(&timer0Handle);
	
	while(1);
}

void vidSysTickISR(void)
{
	static u8 u8Count = 0;
	u8Count++;
	
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
	UART0_vidSendString("...\r\n");
	if (u8Count == 3)
	{
		APP_vidGetTemperature();
		u8Count = 0;
	}
}

void APP_vidGetTemperature(void)
{
	
	u8 u8RH1 = 0;
	u8 u8RH2 = 0;
	u8 u8Temp1 = 0;
	u8 u8Temp2 = 0;
	u8 u8Checksum = 0;
	DHT11_vidStart();

	if(DHT11_u8CheckResponse() == DHT11_RESPONSE_GOOD)
	{

		u8RH1 = DHT11_u8ReadByte();
		u8RH2 = DHT11_u8ReadByte();
		u8Temp1 = DHT11_u8ReadByte();
		u8Temp2 = DHT11_u8ReadByte();
		u8Checksum = DHT11_u8ReadByte();
		
	if ((u8RH1 + u8RH2 + u8Temp1 + u8Temp2) == u8Checksum)
	{
		UART0_vidSendString("Checksum: Good.\r\n");
	}
	else 
	{
		UART0_vidSendString("Checksum: Bad.\r\n");
	}
	
		UART0_vidSendString("Temperature: ");
		UART_vidSendNumber(UART0_vidSendByte,u8Temp1);	
		UART0_vidSendString(" C");
		UART0_vidSendByte('\r');
		UART0_vidSendByte('\n');
		UART0_vidSendString("Humidity: ");
		UART_vidSendNumber(UART0_vidSendByte,u8RH1);
		UART0_vidSendString("%");
		UART0_vidSendByte('\r');
		UART0_vidSendByte('\n');
	}
	else
	{
		UART0_vidSendString("Error: Response.\r\n");
	}
}