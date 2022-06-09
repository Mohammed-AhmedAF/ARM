#include <stdint.h>
#include <FreeRTOS.h>
#include <task.h>
#include "Std_Types.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include <event_groups.h>

typedef enum
{
off,on
}ledstate;
ledstate blue;
EventGroupHandle_t myEventGroup;

void vPeriodicTask(void *pvParameters)
{
	
	// Establish the task's period.
	const TickType_t xDelay = pdMS_TO_TICKS(550) ;
	TickType_t xLastWakeTime = xTaskGetTickCount();

	for (;;) {		

		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN3);
		vTaskDelayUntil(&xLastWakeTime, xDelay);

		xEventGroupSetBits(myEventGroup,0x01);

		// Block until the next release time.
	}

}

void vBlinkRed(void * pvParameters)
{
	const TickType_t xDelay = pdMS_TO_TICKS(550);
	TickType_t xLastWakeTime = xTaskGetTickCount();
	EventBits_t xEventGroupValue;
	
	for (;;)
	{
		xEventGroupValue = xEventGroupWaitBits(myEventGroup,0x01,pdTRUE,pdTRUE,portMAX_DELAY);
		if (xEventGroupValue == 0x01)
		{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
		}
	}
}
	
int main()
{
	//init blue led state
	blue=off;
	
	//init gpio pins
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);

	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	
	myEventGroup = xEventGroupCreate();

	
	//create blink led task
	xTaskCreate(vPeriodicTask, "My Task ",200, NULL, 1, NULL);
	xTaskCreate(vBlinkRed, "My Task ",200, NULL, 1, NULL);

	// Startup of the FreeRTOS scheduler.  The program should block here.
	vTaskStartScheduler();

	// The following line should never be reached.  Failure to allocate enough
	//	memory from the heap would be one reason.
	for (;;);
	
}

