/*
An example of software timer, the period of the timer is changed from an ISR
*/

#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "NVIC_interface.h"
#include "TM4C123.h"                    // Device header

void vidChangePeriod(void);
void vidBlink(TimerHandle_t xTimer);
void vidChangePeriod(void);
volatile u8 u8PeriodFlag = 0;

static TimerHandle_t blinkTimerHandle = NULL;


void vidBlink(TimerHandle_t xTimer)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);

}

void vidChangePeriod(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	u16 u16MSValue;
	if (u8PeriodFlag == 0)
	{
		u16MSValue = 1000;
		u8PeriodFlag = 1;
	}
	else
	{
		u16MSValue = 50;
		u8PeriodFlag = 0;
	}
	xTimerChangePeriodFromISR(blinkTimerHandle,pdMS_TO_TICKS(u16MSValue),&xHigherPriorityTaskWoken);

	if (xHigherPriorityTaskWoken != pdFALSE)
	{
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN0);
}


int main(void)
{
	/*Enable running to peripheral*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	
	/*Pin configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	
	/*It is necessary to unlockl the port befor making configuration to the input pin*/
	GPIO_vidUnlock(GPIO_PORTF);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN0);
	GPIO_vidLock(GPIO_PORTF);
	
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN0,GPIO_INPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN0,GPIO_DEN_SET);
	
	/*External interrupt configuration*/
	ExtInterruptConfig_t extBtn0Config;
	extBtn0Config.ptrFunc = vidChangePeriod;
	extBtn0Config.u8BothEdges = GPIO_INTERRUPT_EVENTCONTROLLED;
	extBtn0Config.u8InterruptEvent = GPIO_EVENT_FALLINGEDGE;
	extBtn0Config.u8InterruptSense = GPIO_SENSE_EDGE;
	extBtn0Config.u8PullResistance = GPIO_PUR_ENABLED;
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN0,&extBtn0Config);

	NVIC_vidSetInterrupt(NVIC_GPIOF);
	NVIC_vidSetPriority(NVIC_GPIOF,6);
	
	/*Creating auto-reload timer*/
	blinkTimerHandle = xTimerCreate("blink",pdMS_TO_TICKS(100),pdTRUE,(void*) 0,vidBlink);
	xTimerStart(blinkTimerHandle,portMAX_DELAY);
	
	__enable_irq();
	
	vTaskStartScheduler();

	while(1);
}
