#include "osKernel.h"
#include "Macros.h"
#include "TIMER0_interface.h"

#define NUM_OF_THREADS 3
#define STACKSIZE 100
#define BUS_FREQ 16000000
/*Total number of periodic threads allowed*/
#define NUM_PERIODIC_TASK 5

uint32_t MILLIS_PRESCALER = 0;
/*Function prototype of function defined in osKernel.s*/
void osSchedulerLaunch(void);

uint32_t periodicTick = 0;
void (*periodicTask) (void);

#define PERIOD 100

#define SYSPRI3 (*((volatile uint32_t *)0xE000ED20))
#define INTCTRL (*((volatile uint32_t *)0xE000ED04))
	

tcb_t tcbs[NUM_OF_THREADS];
tcb_t * currentPt;

static periodicTaskT periodicTasks[NUM_PERIODIC_TASK];

int32_t TCB_STACK[NUM_OF_THREADS][STACKSIZE];
static uint32_t TimeMSec;
static uint32_t MaxPeriod;
static uint32_t NumPeriodicThreads;

/*Initialize the stack*/
void osKernelStackInit(int i)
{
 tcbs[i].stackPt = &TCB_STACK[i][STACKSIZE-16]; /*Stack pointer*/
 TCB_STACK[i][STACKSIZE-1] = 0x01000000;
}

uint8_t osKernelAddPeriodicThread(void (*thread) (void), uint32_t period)
{
	if ((NumPeriodicThreads == NUM_PERIODIC_TASK) || (period == 0))
	{
		return 0;
	}
	
	/*Store thread*/
	periodicTasks[NumPeriodicThreads].task = thread;
	periodicTasks[NumPeriodicThreads].period = period;
	periodicTasks[NumPeriodicThreads].timeLeft = period-1;
	
	return 1;
}

void periodic_thread_execute(void)
{
	uint8_t threadIndex;
	for (threadIndex = 0; threadIndex < NUM_PERIODIC_TASK; threadIndex++)
	{
		if (periodicTasks[threadIndex].timeLeft == 0 && (periodicTasks[threadIndex].task != NULL))
		{
			periodicTasks[threadIndex].task();
			periodicTasks[threadIndex].timeLeft = periodicTasks[threadIndex].period - 1;
		}
		else
		{
			periodicTasks[threadIndex].timeLeft--;
		}
	}
	
	for (threadIndex = 0; threadIndex < NUM_OF_THREADS; threadIndex++)
	{
		if (tcbs[threadIndex].sleepTime != 0 && tcbs[threadIndex].stackPt != NULL)
		{
		tcbs[threadIndex].sleepTime--;
		}
	}
}

void (*periodicTask)(void);
void osPeriodicTask_Init(void (*task) (void), uint32_t freq, uint8_t priority)
{
	TIMER0_vidInit();
	NVIC_GetEnableIRQ(19);
	NVIC_SetPriority(19,priority);
	periodicTask = periodic_thread_execute;
	TIMER0_vidPutISRFunction(periodicTask);
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
	
	/*Initializing sleepTime to 0, meaning no sleep time*/
	for (int i = 0; i < NUM_OF_THREADS; i++)
	{
		tcbs[i].sleepTime = 0;
	}
	
	__enable_irq();
	
	return 1;
}

void osKernelInit(void)
{
	__disable_irq();
	MILLIS_PRESCALER = (BUS_FREQ/1000);
	TIMER0_vidInit();
	TIMER0_vidPutISRFunction(periodic_thread_execute);
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
	currentPt = currentPt->next;
	while(currentPt->sleepTime > 0)
	{
		currentPt = currentPt->next;
	}
}

void osKernelPutPeriodicTask(void (*perTask) (void))
{
	periodicTask = perTask;
}


uint8_t osAddPeriodicFunctions(
void (*threadF1)(void), uint32_t period1,
void (*threadF2)(void), uint32_t period2
)
{

	/*Assign task parameters to array*/
	periodicTasks[0].task = threadF1;
	periodicTasks[0].period = period1;
	periodicTasks[0].timeLeft = period1-1;
	
	periodicTasks[1].task = threadF2;
	periodicTasks[1].period = period2;
	periodicTasks[1].timeLeft = period2-1;

	return 1;	
	
}

void osKernelAddPeriodicTask(void (*ptrF) (void), uint32_t period)
{
	static uint32_t taskIndex = 0;
	periodicTasks[taskIndex].task = ptrF;
	periodicTasks[taskIndex].period = period;
	periodicTasks[taskIndex].timeLeft = period-1;
	
	taskIndex++;
}

void osThreadSleep(uint32_t sleep_time)
{
	__disable_irq();
	currentPt->sleepTime = sleep_time;
	__enable_irq();
		
	osThreadYield();

}