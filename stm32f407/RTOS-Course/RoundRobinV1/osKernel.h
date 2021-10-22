#ifndef _OS_KERNEL_H
#define _OS_KERNEL_H
//#include "stm32f4xx.h"                  // Device header
#include "TM4C123.h"                    // Device header

#include <stdint.h>
void osKernelLaunch(uint32_t quanta);
void osKernelInit(void);
void osKernelStackInit(int i);
void osThreadYield(void);
void osSemaphoreInit(uint32_t * pu32Semaphore, uint32_t u32Value);
void osSemaphoreSet(uint32_t * pu32Semaphore);
void osSemaphoreWait(uint32_t * pu32Semaphore);

uint8_t osKernelAddThreads(void (*task0) (void),
														void (*task1)(void),
														void (*task2) (void)
															);
	
#endif