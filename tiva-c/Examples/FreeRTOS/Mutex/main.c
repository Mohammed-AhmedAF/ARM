#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

void vidTask1(void * ptrArg);
void vidTask2(void * ptrArg);
SemaphoreHandle_t mySemaphore = NULL;

void vidTask1(void * ptrArg)
{
	const TickType_t xDelay = pdMS_TO_TICKS(1000) ;
	TickType_t xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
	vTaskDelayUntil(&xLastWakeTime,pdMS_TO_TICKS(50));
      	xSemaphoreTake(mySemaphore,portMAX_DELAY);
		for (u8 i = 0; i < 10; i++)
		{
			GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);
			vTaskDelay(xDelay);
		}
			xSemaphoreGive(mySemaphore);
      vTaskDelayUntil(&xLastWakeTime, xDelay);

	}
}

void vidTask2(void * ptrArg)
{
	const TickType_t xDelay = pdMS_TO_TICKS(700);
	while(1)
	{
		TickType_t xLastWakeTime = xTaskGetTickCount();

		vTaskDelayUntil(&xLastWakeTime,pdMS_TO_TICKS(100));
		xSemaphoreTake(mySemaphore,portMAX_DELAY);
		for (u8 i = 0; i < 20; i++)
		{
			GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_BLUE);
			vTaskDelay(xDelay);
		}
		xSemaphoreGive(mySemaphore);

	}
}




int main(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
	mySemaphore = xSemaphoreCreateMutex();
	
	xTaskCreate(vidTask1,"Blink2",100,NULL,1,NULL);
	xTaskCreate(vidTask2,"Blink3",100,NULL,1,NULL);

	vTaskStartScheduler();
}
