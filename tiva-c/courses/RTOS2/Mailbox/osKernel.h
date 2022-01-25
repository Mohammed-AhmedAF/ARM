#ifndef _OS_KERNEL_H
#define _OS_KERNEL_H
#include <stdint.h>
#include "TM4C123.h"                    // Device header

/*Function declarations*/
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
uint8_t osKernelAddPeriodicThread(void (*task) (void), uint32_t period);
void periodic_thread_execute(void);
void osPeriodicTask_Init(void (*task) (void), uint32_t freq, uint8_t priority);
void osThreadSleep(uint32_t sleep_time);
void osKernelAddPeriodicTask(void (*ptrF) (void), uint32_t period);
/*Semaphore functions*/
void osSemaphoreInit(int32_t * semaphore, int32_t value);
void osSemaphoreWait(int32_t * semaphore);
void osSemaphoreSet(int32_t * semaphore);
void osSemaphoreWaitCooperative(int32_t * semaphore);

/*Mailbox function*/
void osMailboxInit(void);
void osMailboxSend(uint32_t data);
uint32_t osMailboxReceive(void);

/*Typedefs and macros*/
typedef void(*taskT) (void);
#define NULL (void*)0 
typedef int32_t Semaphore_t;
typedef struct 
{
	taskT task;
	uint32_t period;
	uint32_t timeLeft;
}periodicTaskT;

struct tcb
{
	int32_t * stackPt;
	struct tcb * next;
	int32_t sleepTime;
};

typedef struct tcb tcb_t;


#endif