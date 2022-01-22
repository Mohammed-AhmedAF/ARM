#include "osKernel.h"
#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "NVIC_interface.h"

#define QUANTA 10
void Task0(void);
void Task1(void);
void Task2(void);


static uint32_t	count1 = 0;
static uint32_t count0 = 0;
static uint32_t count2 = 0;

int32_t semaphore1, semaphore2;
int32_t semaphoreSporadic;

void Task0(void)
{

	while(1)
	{
		osSignalSet(&semaphore2);
		osSignalWait(&semaphore1);
		count0++;
	}
}

void Task1(void)
{
	while(1)
	{
	count1++;
		osSignalWait(&semaphore2);
		osSignalSet(&semaphore1);
	}
}

void Task2(void)
{
	while(1)
	{
	osSignalWait(&semaphoreSporadic);
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_BLUE);
	count2++;
	}
}

void vidTriggerSporadic(void)
{
	osSignalSet(&semaphoreSporadic);
	GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN0);
}

int main(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	
	/*GPIO LED configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_GREEN,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DEN_SET);
	
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_BLUE,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_BLUE,GPIO_OUTPUT);
	
	GPIO_vidUnlock(GPIO_PORTF);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN0);
	
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN0,GPIO_INPUT);
	
	ExtInterruptConfig_t strctExtConfig;
	strctExtConfig.ptrFunc = vidTriggerSporadic;
	strctExtConfig.u8BothEdges = GPIO_INTERRUPT_EVENTCONTROLLED;
	strctExtConfig.u8InterruptEvent = GPIO_EVENT_FE;
	strctExtConfig.u8InterruptSense = GPIO_SENSE_EDGE;
	strctExtConfig.u8PullResistance = GPIO_PUR_ENABLED;
	
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN0,&strctExtConfig);
	
	NVIC_vidSetInterrupt(NVIC_GPIOF);
	
	/*Initiate UART*/
	osSemaphoreInit(&semaphore1,1);
	osSemaphoreInit(&semaphore2,0);
	osSemaphoreInit(&semaphoreSporadic,0);
	
	osKernelInit();
	osKernelAddThreads(&Task0,&Task1,&Task2);
	osKernelLaunch(QUANTA);
}