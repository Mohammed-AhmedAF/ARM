#include "Macros.h"
#include "STD_TYPES.h"
#include <FreeRTOS.h>
#include <task.h>
#include <event_groups.h>
#include "SYSCNTRL_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"

void vidToggleLEDs(void * ptrParam);
void vidProcessButtons(void);


#define RED_EVENT_BIT 0x01
#define BLUE_EVENT_BIT 0x10

static EventGroupHandle_t myEventGroup;
TaskHandle_t redTaskHandle;

void vidToggleLEDs(void * ptrParam)
{
	const TickType_t xDelay = pdMS_TO_TICKS(1000);
	TickType_t xLastWakeTime = xTaskGetTickCount();
	EventBits_t receivedEvents;
	while(1)
	{
		receivedEvents = xEventGroupWaitBits(myEventGroup,RED_EVENT_BIT|BLUE_EVENT_BIT,pdTRUE,pdFALSE,portMAX_DELAY);
		if (receivedEvents == RED_EVENT_BIT)
		{
			GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
		}
		else if (receivedEvents == BLUE_EVENT_BIT)
		{
			GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN2);


		}
	}
}


void vidProcessButtons(void)
{
	BaseType_t xHigherPriorityTaskWoken, xResult;
	xHigherPriorityTaskWoken = pdFALSE;
	
	if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN0))
	{
		xEventGroupSetBitsFromISR(myEventGroup,RED_EVENT_BIT,&xHigherPriorityTaskWoken);
		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken)
		GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN0);
	}
	else if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN4)) 
	{
		xEventGroupSetBitsFromISR(myEventGroup,BLUE_EVENT_BIT,&xHigherPriorityTaskWoken);
				portEND_SWITCHING_ISR(xHigherPriorityTaskWoken)

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
	NVIC_vidSetPriority(NVIC_GPIOF,6);
	
	/*Event group*/
	myEventGroup = xEventGroupCreate();
	
	/*Creating RTOS tasks*/
	xTaskCreate(vidToggleLEDs,"Toggling",100,NULL,1,&redTaskHandle);
	
	vTaskStartScheduler();
	
	__enable_irq();
	
	while(1);
}