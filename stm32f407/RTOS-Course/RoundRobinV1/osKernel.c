#include "osKernel.h"
#include "stm32f4xx.h"                  // Device header


#define SYSPRI3 (*((volatile uint32_t *) 0xE000ED20))
void osSchedulerLaunch(void);

/*We have to make sure that the stack pointer of each thread
points to the top of the stack.
*/

#define BUS_FREQ 16000000
uint32_t MILLIS_PRESCALER;
#define NUMBER_OF_THREADS 3
#define STACK_SIZE 100


struct tcb {
	int32_t *stackPt;
	struct tcb * nextPt;
};

typedef struct tcb tcbtype;
tcbtype tcbs[NUMBER_OF_THREADS];
tcbtype * currentPt;

/*Holding the stack of each thread*/
int32_t TCB_STACK[NUMBER_OF_THREADS][STACK_SIZE];

/*Parameter i: thread number*/
void osKernelStackInit(int i) {
	tcbs[i].stackPt = &TCB_STACK[i][STACK_SIZE-16];
	/*Initialize XPSR*/
	TCB_STACK[i][STACK_SIZE-1] = 0x01000000;

}

uint8_t osKernelAddThreads(void (*task0) (void),
														void (*task1)(void),
														void (*task2) (void)
															)
{
	__disable_irq();
	tcbs[0].nextPt = &tcbs[1];
	tcbs[1].nextPt = &tcbs[2];
	tcbs[2].nextPt = &tcbs[0];
	
	osKernelStackInit(0);
	/*pointed the program counter register to the function of the task*/
	TCB_STACK[0][STACK_SIZE-2] = (int32_t)(task0);
	
	osKernelStackInit(1);
	/*pointed the program counter register to the function of the task*/
	TCB_STACK[1][STACK_SIZE-2] = (int32_t)(task1);
	
	osKernelStackInit(2);
	/*pointed the program counter register to the function of the task*/
	TCB_STACK[2][STACK_SIZE-2] = (int32_t)(task2);
	
	currentPt = &tcbs[0];
	
	__enable_irq();
	return 1;
}

/*Initialize systick*/
/*Define priority of systick*/
/*Launch scheduler*/
void osKernelLaunch(uint32_t quanta)
{
	/*Disable systick*/
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
	
	SysTick->LOAD = (quanta*MILLIS_PRESCALER)-1;
	
	/*Set priority of systick*/
	SYSPRI3 = (SYSPRI3&0xFFFFFFFF) | 0xE0000000;
	
	/*Enable systick*/	
	SysTick->CTRL = 0x00000007;
	
	/*Launch scheduler*/
	osSchedulerLaunch();
	
}

void osKernelInit(void)
{
	
	__disable_irq();
	
	MILLIS_PRESCALER = BUS_FREQ/1000;
	__enable_irq();

}