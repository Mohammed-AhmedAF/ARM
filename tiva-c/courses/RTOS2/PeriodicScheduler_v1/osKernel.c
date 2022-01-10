#include "osKernel.h"
#include "Macros.h"

#define NUM_OF_THREADS 3
#define STACKSIZE 100
#define BUS_FREQ 16000000

uint32_t MILLIS_PRESCALER = 0;
/*Function prototype of function defined in osKernel.s*/
void osSchedulerLaunch(void);

uint32_t periodicTick = 0;
void (*periodicTask) (void);

#define PERIOD 100

#define SYSPRI3 (*((volatile uint32_t *)0xE000ED20))
#define INTCTRL (*((volatile uint32_t *)0xE000ED04))
	
struct tcb
{
	int32_t * stackPt;
	struct tcb * next;
};

typedef struct tcb tcb_t;
tcb_t tcbs[NUM_OF_THREADS];
tcb_t * currentPt;

int32_t TCB_STACK[NUM_OF_THREADS][STACKSIZE];

/*Initialize the stack*/
void osKernelStackInit(int i)
{
 tcbs[i].stackPt = &TCB_STACK[i][STACKSIZE-16]; /*Stack pointer*/
 TCB_STACK[i][STACKSIZE-1] = 0x01000000;
}

uint8_t osKernelAddThreads(void (*Task0) (void),void (*Task1) (void),void (*Task2) (void))
{
	/*To ensure that the function is atomic*/
	__disable_irq();
	tcbs[0].next = &tcbs[1];
	tcbs[1].next = &tcbs[2];
	tcbs[2].next = &tcbs[0];
	
	
	osKernelStackInit(0);
	/*Point PC to thread function*/
	TCB_STACK[0][STACKSIZE-2] = (int32_t) (Task0);
	
	osKernelStackInit(1);
	/*Point PC to thread function*/
	TCB_STACK[1][STACKSIZE-2] = (int32_t) (Task1);
	
	osKernelStackInit(2);
	/*Point PC to thread function*/
	TCB_STACK[2][STACKSIZE-2] = (int32_t) (Task2);
	
	currentPt = &tcbs[0];
	
	__enable_irq();
	
	return 1;
}

void osKernelInit(void)
{
	__disable_irq();
	MILLIS_PRESCALER = (BUS_FREQ/1000);
	__enable_irq();
	
}

/*Initialize SysTick*/
void osKernelLaunch(uint32_t quanta)
{
	/*Disabling SysTick*/
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
	SysTick->LOAD = (quanta*MILLIS_PRESCALER)-1;
	SYSPRI3 = (SYSPRI3&0x00FFFFFF) | 0xE0000000; /*Priority 7*/
	
	SysTick->CTRL = 0x00000007;
	osSchedulerLaunch();
}


void SysTick_Handler()
{
	/*Trigger PendSV*/
	SET_BIT(INTCTRL,28);
}

void osThreadYield(void)
{
	SysTick->VAL = 0;
	INTCTRL = 0x04000000; // trigger SysTick
}

/*Periodic tasks run to completion*/
void osPeriodicScheduler(void)
{
	periodicTick++;
	if (periodicTick == PERIOD)
	{
		(*periodicTask)();
		periodicTick = 0;
	}
	currentPt = currentPt->next;
}

void osKernelPutPeriodicTask(void (*perTask) (void))
{
	periodicTask = perTask;
}