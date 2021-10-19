#ifndef _OS_KERNEL_H
#define _OS_KERNEL_H

#include <stdint.h>

void osKernelLaunch(uint32_t quanta);
void osKernelInit(void);
void osKernelStackInit(int i);

uint8_t osKernelAddThreads(void (*task0) (void),
														void (*task1)(void),
														void (*task2) (void)
															);
	
#endif