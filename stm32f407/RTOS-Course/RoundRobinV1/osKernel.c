#include "osKernel.h"

#define SYSPRI3         (*((volatile uint32_t *)0xE000ED20))
#define INTCTRL         (*((volatile uint32_t *)0xE000ED04))


void  osSchedulerLaunch(void);

#define NUM_OF_THREADS  3        
#define STACKSIZE   100      


#define BUS_FREQ 				16000000
uint32_t MILLIS_PRESCALER;

struct tcb{
  int32_t *stackPt;       
  struct tcb *nextPt;  
};

typedef struct tcb tcbType;
tcbType tcbs[NUM_OF_THREADS];
tcbType *currentPt;

int32_t TCB_STACK[NUM_OF_THREADS][STACKSIZE];

void osKernelStackInit(int i){
  tcbs[i].stackPt = &TCB_STACK[i][STACKSIZE-16]; 
  TCB_STACK[i][STACKSIZE-1] = 0x01000000;  
}



uint8_t osKernelAddThreads(void(*task0)(void),void(*task1)(void),void(*task2)(void))
	{ 
	__disable_irq();
  tcbs[0].nextPt = &tcbs[1]; 
  tcbs[1].nextPt = &tcbs[2]; 
  tcbs[2].nextPt = &tcbs[0]; 
  osKernelStackInit(0);
	/*Program Counter (PC) to hold address of the thread*/
	TCB_STACK[0][STACKSIZE-2] = (int32_t)(task0); 
  
	osKernelStackInit(1);
	TCB_STACK[1][STACKSIZE-2] = (int32_t)(task1); 
  
	osKernelStackInit(2);
	TCB_STACK[2][STACKSIZE-2] = (int32_t)(task2); 
	currentPt = &tcbs[0];
 __enable_irq();
		return 1;              
}

void osKernelInit(void)
{
     __disable_irq();
		 MILLIS_PRESCALER=(BUS_FREQ/1000);

}

void osKernelLaunch(uint32_t quanta)
{
	SysTick->CTRL =0;
	SysTick->VAL=0;
	SysTick->LOAD = (quanta* MILLIS_PRESCALER)-1;
  	SYSPRI3 =(SYSPRI3&0x00FFFFFF)|0xE0000000; // priority 7

	SysTick->CTRL =0x00000007;
	osSchedulerLaunch();
}

 void osThreadYield(void)
 {
			SysTick->VAL = 0;
	    INTCTRL = 0x04000000; // trigger SysTick

 }

void osSemaphoreInit(uint32_t * pu32Semaphore, uint32_t u32Value)
{
	*pu32Semaphore = u32Value;
}

void osSemaphoreSet(uint32_t * pu32Semaphore)
{
__disable_irq();
	*pu32Semaphore+=1;
__enable_irq();

}

void osSemaphoreWait(uint32_t * pu32Semaphore)
{
	__disable_irq();
	while(*pu32Semaphore <= 0)
	{
		__disable_irq();
		/*Cooperative semaphore*/
		osThreadYield();
		__enable_irq();
	}
	*pu32Semaphore-=1;
	__enable_irq();

}

 
