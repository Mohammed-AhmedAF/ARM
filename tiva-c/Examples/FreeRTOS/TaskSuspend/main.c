#include <FreeRTOS.h>
#include <task.h>>
#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "NVIC_interface.h"

void taskBlinkGreenLED(void * ptrParam);
void taskBlinkRedLED(void * ptrParam);
void vidProcessSwitch(void);

TaskHandle_t blinkGreenLEDHandle;
TaskHandle_t blinkRedLEDHandle;

void taskBlinkGreenLED(void * ptrParam)
{

	while(1)
	{
		vTaskSuspend(blinkGreenLEDHandle);
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);
	}
}

void taskBlinkRedLED(void * ptrParam)
{

	while(1)
	{
		vTaskSuspend(blinkRedLEDHandle);
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_RED);
	}
}

void vidProcessSwitch(void)
{
	if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN0) == 1)
	{
		xTaskResumeFromISR(blinkGreenLEDHandle);
		GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN0);
	}
	else if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN4) == 1)
	{
		xTaskResumeFromISR(blinkRedLEDHandle);
		GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN4);
	}

}

int main(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_GREEN,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_RED,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_RED,GPIO_DEN_SET);
	
	GPIO_vidUnlock(GPIO_PORTF);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN0);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN4);
	GPIO_vidLock(GPIO_PORTF);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN0,GPIO_INPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN0,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN4,GPIO_INPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN4,GPIO_DEN_SET);
	
	ExtInterruptConfig_t switch0Config;
	switch0Config.ptrFunc = vidProcessSwitch;
	switch0Config.u8BothEdges = GPIO_INTERRUPT_BOTHEDGES;
	switch0Config.u8InterruptEvent = GPIO_EVENT_FALLINGEDGE;
	switch0Config.u8PullResistance = GPIO_PUR_ENABLED;
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN0,&switch0Config);
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN4,&switch0Config);

	NVIC_vidSetInterrupt(NVIC_GPIOF);
	NVIC_vidSetPriority(NVIC_GPIOF,5);
	
	__enable_irq();
	
	xTaskCreate(taskBlinkGreenLED,"blink",100,NULL,1,&blinkGreenLEDHandle);
	xTaskCreate(taskBlinkRedLED,"blinkRed",100,NULL,1,&blinkRedLEDHandle);
	vTaskStartScheduler();
	
	while(1);
	
}