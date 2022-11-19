#include <FreeRTOS.h>
#include <task.h>
#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "UART_interface.h"
#include "NVIC_interface.h"

/*taskParam: Variable to be casted as parameter for the task function*/
typedef struct {
	u8 u8Led;
	u16 u16Ms;
} taskParam;

void vidBlinkTask(void *ptrParam);

void vidBlinkTask(void *ptrParam)
{
	taskParam * taskData = (taskParam *) ptrParam;
	TickType_t delayTime = pdMS_TO_TICKS(taskData->u16Ms);
	
	while(1)
	{
				vTaskDelay(delayTime);

		GPIO_vidTogglePin(GPIO_PORTF,taskData->u8Led);

	}

}

taskParam blink0;
taskParam blink1;

int main(void)
{
	/*Enabling running clock to peripherals*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_GREEN,GPIO_OUTPUT);
	
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_RED,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_RED,GPIO_OUTPUT);
	
	blink0.u8Led = GPIO_LED_GREEN;
	blink0.u16Ms = 100;
	
	blink1.u8Led = GPIO_LED_RED;
	blink1.u16Ms = 50;
	
	/*You will need change the MINIMAL_STACK_SIZE to 128*/
	xTaskCreate(vidBlinkTask,"blinker0",120, (void *) &blink0,1,NULL);
	xTaskCreate(vidBlinkTask,"toto",120, (void*) &blink1,1,NULL);

	vTaskStartScheduler();
	
	
 while(1);
}
