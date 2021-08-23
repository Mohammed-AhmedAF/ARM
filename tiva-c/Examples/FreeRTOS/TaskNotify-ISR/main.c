#include "Macros.h"
#include "STD_TYPES.h"
#include <FreeRTOS.h>
#include <task.h>
#include <event_groups.h>
#include "SYSCNTRL_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"

void vidToggleRed(void * ptrParam);
void vidToggleBlue(void * prtParam);
void vidProcessButtons(void);
void vidTestBlinking(void * ptrParam);
volatile u8 u8SpeedFlag = 0;

static EventGroupHandle_t myEventGroup;
TaskHandle_t redTaskHandle;
TaskHandle_t blueTaskHandle;

void vidToggleRed(void * ptrParam)
{
	EventBits_t receivedEvents;
	while(1)
	{
		receivedEvents = ulTaskNotifyTake(pdFALSE,portMAX_DELAY);
		if (receivedEvents == 1)
		{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
		}
		else if (receivedEvents == 0x10)
		{
				

		}
	}
}

void vidToggleBlue(void * ptrParam)
{

	while(1)
	{
			if (ulTaskNotifyTake(pdFALSE,portMAX_DELAY) == 1)
			{
				GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN2);

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

	if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN0) == 1)
	{
		vTaskNotifyGiveFromISR(redTaskHandle,&HigherPriorityTaskWoken);
		GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN0);
	}
	else if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN4) == 1)
	{
		vTaskNotifyGiveFromISR(blueTaskHandle,&HigherPriorityTaskWoken);
		GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN4);

	}
}

int main(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	
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
	
	/*Creating RTOS tasks*/
	xTaskCreate(vidToggleRed,"red",100,NULL,1,&redTaskHandle);
	xTaskCreate(vidToggleBlue,"blue",100,NULL,1,&blueTaskHandle);
	
	/*Running the RTOS scheduler*/
	vTaskStartScheduler();
	
	while(1);
}
