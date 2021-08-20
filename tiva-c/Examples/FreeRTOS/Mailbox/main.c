#include "Macros.h"
#include "STD_TYPES.h"
#include <FreeRTOS.h>
#include <task.h>
#include <event_groups.h>
#include <queue.h>

#include "SYSCNTRL_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"
#include "UART_interface.h"

void vidToggleBlue(void * prtParam);
void vidProcessButtons(void);
void vidTestBlinking(void * ptrParam);
void vidHandleUART(void);
void vidUARTCompanion(void * prtParam);
volatile u8 u8SpeedFlag = 0;

TaskHandle_t redTaskHandle;
TaskHandle_t uartTaskHandle;
TaskHandle_t uartCompanionHandle;
QueueHandle_t xMailbox;

volatile  u8 u8Char;


static QueueHandle_t xQueue;
void vidToggleRed(void * ptrParam)
{
	EventBits_t receivedEvents;
	u8 u8Char = 'i';
	while(1)
	{
		if(xQueueReceive(xMailbox,&u8Char,0) == 1)
		{
		if (u8Char == 'r')
		{
			GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
		}
		else if (u8Char == 'b')
		{
			GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN2);
		}
	}
		else if (u8Char == 0x10)
		{
				UART0_vidSendByte(u8Char);

		}
	}
}


void vidTestBlinking(void * ptrParam)
{
	TickType_t xDelay = pdMS_TO_TICKS(1000);
	TickType_t xLastWakeUp = xTaskGetTickCount();
	u8 u8Count = 0;
	while(1)
	{
		
		
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN3);
		if (u8SpeedFlag == 1)
		{
			u8SpeedFlag = 0;
			xDelay = pdMS_TO_TICKS(200);

		}
		else
		{
			xDelay = pdMS_TO_TICKS(1000);
		}
		vTaskDelayUntil(&xLastWakeUp,xDelay);
		
		u8Count++;
		if (u8Count == 5)
		{
			u8Count = 0;

		}
	}
}

void vidProcessButtons(void)
{
	BaseType_t HigherPriorityTaskWoken;
	HigherPriorityTaskWoken = pdFALSE;
	u8 u8A = 'r';
	if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN0) == 1)
	{
		xQueueOverwriteFromISR(xMailbox,&u8A,&HigherPriorityTaskWoken);
		//vTaskNotifyGiveFromISR(redTaskHandle,&HigherPriorityTaskWoken);
		GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN0);
		if (HigherPriorityTaskWoken == pdTRUE)
		{
			portYIELD_FROM_ISR(HigherPriorityTaskWoken);
		}
	}
	else if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN4) == 1)
	{
		u8A = 'b';
		xQueueOverwriteFromISR(xMailbox,&u8A,&HigherPriorityTaskWoken);
		if (HigherPriorityTaskWoken == pdTRUE)
		{
			portYIELD_FROM_ISR(HigherPriorityTaskWoken);
		}
		GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN4);

	}
}

void vidUARTCompanion(void * ptrParam)
{
	while(1)
	{
	vTaskSuspend(NULL);
	if (u8Char == 'a')
	{
					GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN3);

	}
	else
	{
	UART0_vidSendByte(u8Char);
						GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);

	}
}	
}

void vidHandleUART(void)
{


	BaseType_t xCheckIfYieldRequied;
	u8Char = UART0_u8GetReceivedByte();
	xCheckIfYieldRequied = xQueueSendToBackFromISR(xQueue,&u8Char,portMAX_DELAY);
	//xCheckIfYieldRequied = xTaskResumeFromISR(uartCompanionHandle);
	portYIELD_FROM_ISR(xCheckIfYieldRequied);

}

int main(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);

	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);
	
	/*Pin unlocking (required)*/
	GPIO_vidUnlock(GPIO_PORTF);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN0);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN4);
	GPIO_vidLock(GPIO_PORTF);
	
	GPIOConfig_t gpioButton0Conf;
	gpioButton0Conf.u8AlternateFunc = GPIO_ALTERFUNC_UNSET;
	gpioButton0Conf.u8DigEnable = GPIO_DEN_SET;
	gpioButton0Conf.u8Direction = GPIO_DIR_INPUT;
	gpioButton0Conf.u8Port = GPIO_PORTF;
	gpioButton0Conf.u8Pin = GPIO_PIN0;
	GPIO_vidConfigurePin(&gpioButton0Conf);
	
	/*For button PF4*/
	gpioButton0Conf.u8Pin = GPIO_PIN4;
	GPIO_vidConfigurePin(&gpioButton0Conf);

	ExtInterruptConfig_t Ext0Conf;
	Ext0Conf.ptrFunc = vidProcessButtons;
	Ext0Conf.u8BothEdges = GPIO_INTERRUPT_EVENTCONTROLLED;
	Ext0Conf.u8InterruptEvent = GPIO_EVENT_FALLINGEDGE;
	Ext0Conf.u8InterruptSense = GPIO_SENSE_EDGE;
	Ext0Conf.u8PullResistance = GPIO_PUR_ENABLED;
	
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN0,&Ext0Conf);
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN4,&Ext0Conf);
	
	NVIC_vidSetInterrupt(NVIC_GPIOF);
	/*Absolutely necessary to change the priority of ISR, otherwise the program
	will go into hard fault.
	*/
	NVIC_vidSetPriority(NVIC_GPIOF,6);
	
	/*UART0 pin configuration*/
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN0,GPIO_INPUT);
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x01);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN1,0x01);
	
	/*UARTConfig*/
	UARTConfig_t uart0Config;
	uart0Config.ptrF = vidHandleUART;
	uart0Config.u16Integer = 104;
	uart0Config.u8Fraction = 11;
	uart0Config.u8FIFOEnabled = UART_FIFO_ENABLED;
	uart0Config.u8HighSpeedEnabled = UART_HIGHSPEED_DIV16;
	uart0Config.u8RxTx = UART_RXTX_BOTH;
	uart0Config.u8InterruptEnabled = UART_INTERRUPT_ENABLED;
	uart0Config.u8WordLength = UART_WORDSIZE_8;
	uart0Config.u8ClockSource = UART_CLOCKSOURCE_RC;
	
	UART0_vidInit(&uart0Config);
	
	NVIC_vidSetInterrupt(NVIC_UART0);
	NVIC_vidSetPriority(NVIC_UART0,5);
	
	/*A mailbox is a queue with a length of 1*/
	xMailbox = xQueueCreate(1,sizeof(u8));

	
	/*Creating RTOS tasks*/
	xTaskCreate(vidToggleRed,"red",100,NULL,1,&redTaskHandle);
	xTaskCreate(vidUARTCompanion,"companion",100,NULL,1,&uartCompanionHandle);

	vTaskStartScheduler();
	
	__enable_irq();
	
	while(1);
}