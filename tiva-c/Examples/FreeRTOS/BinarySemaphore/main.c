#include "FreeRTOS.h"
#include "task.h"
#include "Macros.h"
#include "semphr.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "UART_interface.h"

/*Task declarations*/
void LEDOnTask(void * ptr);
void LEDOffTask(void * ptr);

SemaphoreHandle_t binSemaphore;


void LEDOnTask(void * ptr)
{
	static u8 i = 0;
	while(1)
	{
		xSemaphoreTake(binSemaphore,portMAX_DELAY);
		for (i = 0; i < 5; i++)
		{
			GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_BLUE);
			UART0_vidSendString("In LEDOnTask\r\n");
			vTaskDelay(1000);
		}
		xSemaphoreGive(binSemaphore);
		vTaskDelay(1);

	}
}

void LEDOffTask(void * ptr)
{
		static u8 i = 0;

	while(1)
	{
		vTaskDelay(1);

		xSemaphoreTake(binSemaphore,portMAX_DELAY);

		for (i = 0; i < 10; i++)
		{
			UART0_vidSendString("In LEDOffTask\r\n");
			GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_RED);
			vTaskDelay(500);
		}
		xSemaphoreGive(binSemaphore);
		vTaskDelay(1);

	}
}

int main(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	
	/*UART GPIO pin configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN0,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x1);
	
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN1,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN1,0x1);
	
	UARTConfig_t uart0Config;
	uart0Config.u8Module = UART_MODULE_0;
	uart0Config.u8FIFOEnabled = UART_FIFO_DISABLED;
	uart0Config.u8InterruptEnabled = UART_INTERRUPT_DISABLED;
	uart0Config.u8ParitySelect = UART_PARITY_DISABLED;
	uart0Config.u8RxTx = UART_RXTX_BOTH;
	uart0Config.u8WordLength = UART_WORDSIZE_8;
	uart0Config.u8ClockSource = UART_CLOCKSOURCE_RC;
	uart0Config.u8HighSpeedEnabled = UART_HIGHSPEED_DIV16;
	uart0Config.u8StopBits = UART_STOPBITS_1;
	uart0Config.u16Integer = 104;
	uart0Config.u8Fraction = 11;
	UART_vidInit(&uart0Config);

	/*Pin configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	
	xTaskCreate(LEDOnTask,"task1",100,NULL,1,NULL);
	xTaskCreate(LEDOffTask,"task2",100,NULL,1,NULL);

	binSemaphore = xSemaphoreCreateBinary();
	
	/*Semaphore has to be given after creation*/
	/*Removing the xSemaphoreGive statement will cause both tasks to be put in
		a blocked state.
	*/
	xSemaphoreGive(binSemaphore);
	vTaskStartScheduler();
	
	while(1);
	
}