#include "FreeRTOS.h"
#include "task.h"
#include "Macros.h"
#include "semphr.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"

/*Task declarations*/
void task1(void * ptr);
void task2(void * ptr);

SemaphoreHandle_t binSemaphore;


void task1(void * ptr)
{
	static u8 i = 0;
	while(1)
	{
		xSemaphoreTake(binSemaphore,portMAX_DELAY);
		for (i = 0; i < 5; i++)
		{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_BLUE);
		vTaskDelay(1000);
		}
		xSemaphoreGive(binSemaphore);
		vTaskDelay(1);

	}
}

void task2(void * ptr)
{
		static u8 i = 0;

	while(1)
	{
				vTaskDelay(1);

		xSemaphoreTake(binSemaphore,portMAX_DELAY);

		for (i = 0; i < 10; i++)
		{
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
	
	/*Pin configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	
	xTaskCreate(task1,"task1",100,NULL,1,NULL);
	xTaskCreate(task2,"task2",100,NULL,1,NULL);

	binSemaphore = xSemaphoreCreateBinary();
	
	/*Semaphore has to be given after creation*/
	/*Removing the xSemaphoreGive statement will cause both tasks to be put in
		a blocked state.
	*/
	xSemaphoreGive(binSemaphore);
	vTaskStartScheduler();
	
	while(1);
	
}