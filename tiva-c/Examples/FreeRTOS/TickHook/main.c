#include "Macros.h"
#include "STD_TYPES.h"
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"
#include "SYSCNTRL_interface.h"
#include "GPIO_interface.h"

volatile u32 u32Count = 0;

/*A task just put for testing*/
void vidBlinkerTask(void * ptr);
void vidBlinkerTask(void * ptr)
{
	
	while(1)
	{
	
	}
	
}

int main(void)
{
	/*Clock to RCC*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	
	/*LED pin configuration*/
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_GREEN,GPIO_OUTPUT);
	
	/*You will have to create at least one task, otherwise vApplicationTickHook will not be run.*/
	xTaskCreate(vidBlinkerTask,"blinker",100,NULL,1,NULL);
	
	vTaskStartScheduler();
	
	while(1);
}

void vApplicationTickHook(void)
{
	u32Count++;
	if (u32Count == 50)
	{
			u32Count = 0;
			GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);
	}

}