#include "osKernel.h"
#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"

#define QUANTA 10
void Task0(void);
void Task1(void);
void Task2(void);
void pTask1(void);
void pTask2(void);

static uint32_t count0 = 0, count1 = 0, count2 = 0;

void Task0(void)
{

	while(1)
	{
	count0++;
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);
	osThreadSleep(2000);
	}
}

void Task1(void)
{
	while(1)
	{
	count1++;
	}
}

void Task2(void)
{
	while(1)
	{
	count2++;
	}
}

void pTask1(void)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_RED);
}

void pTask2(void)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_BLUE);
}


int main(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_GREEN,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_RED,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_RED,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_BLUE,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_BLUE,GPIO_DEN_SET);
	
	osKernelInit();
	//osKernelAddPeriodicTask(&pTask1,1000);
	//osKernelAddPeriodicTask(&pTask2,1000);

	osKernelAddThreads(Task0,Task1,Task2);
	osKernelLaunch(QUANTA);
}