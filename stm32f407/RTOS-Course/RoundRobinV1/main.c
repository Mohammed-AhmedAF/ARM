#include "osKernel.h"

#define QUANTA 10

void task0(void);
void task1(void);
void task2(void);

uint32_t count0, count1, count2;

void task0(void)
{

	while(1)
	{
		count1++;
	}
}

void task1(void)
{

	while(1)
	{
		count1++;
	}
}

void task2(void)
{

		while(1)
		{
		count2++;
		}
}

int main(void)
{
	osKernelInit();
	osKernelAddThreads(&task0,&task1,task2);
	osKernelLaunch(QUANTA);
	while(1);
}