#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include "Macros.h"
#include "STD_TYPES.h"
#include "SYSCNTRL_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"


static TaskHandle_t blinkerTaskHandle = NULL;

void vidProcessButtons(void);
static u8 u8Count = 0;
void blinkerTask(void * ptrParam);
void blinker2Task(void * ptrParam);

void blinkerTask(void * ptrParam)
{
	TickType_t xLastWakeTime = xTaskGetTickCount();
	TickType_t xDelay = pdMS_TO_TICKS(250);
	while(1)
	{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);
		vTaskDelayUntil(&xLastWakeTime,xDelay);
//		u8Count++;

	}

}

void blinker2Task(void * ptrParam)
{
	TickType_t xLastWakeUpTime = xTaskGetTickCount();
	TickType_t xDelay = pdMS_TO_TICKS(1000);
	u8 u8DeleteFlag = 0;
	while(1)
	{
		//vTaskDelete(NULL);

		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN2);
		vTaskDelayUntil(&xLastWakeUpTime,xDelay);
		if (u8DeleteFlag == 0)
		{
			u8DeleteFlag = 1;
			if (blinkerTaskHandle != NULL)
	{
			vTaskEndScheduler
	}

		}
	}

}

void vidProcessButtons(void)
{
	if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN0) == 1)
	{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
		GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN0);

	}
	else if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN4) == 1)
	{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN2);
		GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN4);

	}
}


int main(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	
	/*On-board pin configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);
	
	
	GPIO_vidUnlock(GPIO_PORTF);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN0);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN4);
	GPIO_vidLock(GPIO_PORTF);
	
	/*Switch 0 pin configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN0,GPIO_INPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN4,GPIO_INPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN4,GPIO_DEN_SET);
	
	
	ExtInterruptConfig_t extInterruptSwtch0;
	extInterruptSwtch0.ptrFunc = vidProcessButtons;
	extInterruptSwtch0.u8BothEdges = GPIO_INTERRUPT_EVENTCONTROLLED;
	extInterruptSwtch0.u8InterruptEvent = GPIO_EVENT_FALLINGEDGE;
	extInterruptSwtch0.u8InterruptSense = GPIO_SENSE_EDGE;
	extInterruptSwtch0.u8PullResistance = GPIO_PUR_ENABLED;
	
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN0,&extInterruptSwtch0);
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN4,&extInterruptSwtch0);

	
	/*NVIC configuration*/
	NVIC_vidSetInterrupt(NVIC_GPIOF);
	NVIC_vidSetPriority(NVIC_GPIOF,5);
	
	xTaskCreate(blinkerTask,"blinker",100,NULL,1,&blinkerTaskHandle);
	xTaskCreate(blinker2Task,"blinker2",100,NULL,1,NULL);
	
	vTaskStartScheduler();
	
	while(1);
}

void vApplicationIdleHook( void )
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);
}
