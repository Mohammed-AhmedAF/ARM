#ifndef _OS_KERNEL_H
#define _OS_KERNEL_H
#include <stdint.h>
#include "TM4C123.h"                    // Device header
void osPeriodicScheduler(void); 
void osKernelLaunch(uint32_t quanta);
void osKernelInit(void);
void osKernelStackInit(int i);
void osSchedulerLaunch(void);
void osThreadYield(void);
uint8_t osKernelAddThreads(void (*Task0) (void),void (*Task1) (void),void (*Task2) (void));
void osKernelPutPeriodicTask(void (*perTask) (void));
uint8_t osAddPeriodicFunctions(
void (*threadF1)(void), uint32_t period1,
void (*threadF2)(void), uint32_t period2
);
typedef void(*taskT) (void);
#define NULL (void*)0 

typedef struct 
{
	taskT task;
	uint32_t period;
}periodicTaskT;


#endif