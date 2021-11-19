

#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "UART_interface.h"
#include "SYSCNTRL_interface.h"
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "semphr.h"

void vidTask1(void * ptrArg);
void vidTask2(void * ptrArg);
SemaphoreHandle_t mySemaphore = NULL;

void vidTask1(void * ptrArg)
{
	const TickType_t xDelay = pdMS_TO_TICKS(200) ;
	TickType_t xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
			vTaskDelayUntil(&xLastWakeTime,pdMS_TO_TICKS(50));
      xSemaphoreTake(mySemaphore,portMAX_DELAY);
		for (u8 i = 0; i < 10; i++)
		{
			GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);
			UART0_vidSendString("Task1 ");
			UART_vidSendNumber(UART0_vidSendByte,i);
			UART0_vidSendString("\r\n");
			vTaskDelay(xDelay);
		}
			xSemaphoreGive(mySemaphore);
      vTaskDelayUntil(&xLastWakeTime, xDelay);

	}
}

void vidTask2(void * ptrArg)
{
	const TickType_t xDelay = pdMS_TO_TICKS(200);
	while(1)
	{
			TickType_t xLastWakeTime = xTaskGetTickCount();

		vTaskDelayUntil(&xLastWakeTime,pdMS_TO_TICKS(100));
		xSemaphoreTake(mySemaphore,portMAX_DELAY);
		for (u8 i = 0; i < 20; i++)
		{
			GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_BLUE);
			UART0_vidSendString("Task2 ");
			UART_vidSendNumber(UART0_vidSendByte,i);
			UART0_vidSendString("\r\n");
			vTaskDelay(xDelay);
		}
		xSemaphoreGive(mySemaphore);

	}
}




int main(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	
	/*LED pins configuration*/
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
	
	/*UART pins configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x1);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x1);
	/*UART Configuration*/
	UARTConfig_t uartConfig;
	uartConfig.u16Integer = 8;
	uartConfig.u8Fraction = 44;
	uartConfig.u8FIFOEnabled = UART_FIFO_ENABLED;
	uartConfig.u8RxTx = UART_RXTX_BOTH;
	uartConfig.u8HighSpeedEnabled  = UART_HIGHSPEED_DIV16;
	uartConfig.u8WordLength = UART_WORDSIZE_8;
	uartConfig.u8ClockSource = UART_CLOCKSOURCE_RC;
	UART0_vidInit(&uartConfig);
	
	/*Mutex creation*/
	mySemaphore = xSemaphoreCreateMutex();
	
	/*Task creation*/
	xTaskCreate(vidTask1,"Blink2",100,NULL,1,NULL);
	xTaskCreate(vidTask2,"Blink3",100,NULL,1,NULL);

	vTaskStartScheduler();
}