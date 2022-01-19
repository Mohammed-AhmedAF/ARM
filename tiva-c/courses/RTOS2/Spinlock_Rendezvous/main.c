#include "osKernel.h"
#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"

#define QUANTA 10
void Task0(void);
void Task1(void);
void Task2(void);


static uint32_t	count1 = 0;
static uint32_t count0 = 0;
static uint32_t count2 = 0;

int32_t semaphore1, semaphore2;

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
	count2++;
	}
}


int main(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_GREEN,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DEN_SET);
	
	/*Initiate UART*/
	osSemaphoreInit(&semaphore1,1);
	osSemaphoreInit(&semaphore2,0);
	
	osKernelInit();
	osKernelAddThreads(&Task0,&Task1,&Task2);
	osKernelLaunch(QUANTA);
}