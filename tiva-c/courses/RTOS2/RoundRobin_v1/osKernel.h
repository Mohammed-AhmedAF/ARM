#ifndef _OS_KERNEL_H
#define _OS_KERNEL_H
#include <stdint.h>
#include "TM4C123.h"                    // Device header

void osKernelLaunch(uint32_t quanta);
void osKernelInit(void);
void osKernelStackInit(int i);
void osSchedulerLaunch(void);
void osThreadYield(void);
uint8_t osKernelAddThreads(void (*Task0) (void),void (*Task1) (void),void (*Task2) (void));

#endif