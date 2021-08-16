#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"

void vidBlink(TimerHandle_t xTimer);
void vidBlink(TimerHandle_t xTimer)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);

}

static TimerHandle_t blinkTimerHandle;

int main(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	
	blinkTimerHandle = xTimerCreate("blink",pdMS_TO_TICKS(500),pdTRUE,(void*) 0,vidBlink);
	xTimerStart(blinkTimerHandle,portMAX_DELAY);
	vTaskStartScheduler();

	while(1);
}