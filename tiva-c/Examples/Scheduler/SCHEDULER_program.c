#include "Macros.h"
#include "STD_TYPES.h"
#include "SYSCNTRL_interface.h"
#include "TIMERS_interface.h"
#include "SysTick_interface.h"
#include "SCHEDULER_interface.h"


static sTask_t * SCHEDULER_tasksArr[SCHEDULER_MAX_TASKS];
TIMERConfig_t timer0AConfig;
SysTickConfig_t SysTickConfig;

void SCHEDULER_vidInit(u8 u8TickSource)	
{
	switch(u8TickSource)
	{
		case SCHEDULER_TICKSOURCE_TIMER0:
		SYSCNTRL_vidEnableTimerClock(SYSCNTRL_TIMER_0);
		break;
		case SCHEDULER_TICKSOURCE_SYSTICK:
			SysTickConfig.ptrFunc = SCHEDULER_vidUpdate;
			SysTickConfig.u8ClockSource = SYSTICK_SYSTEM_CLOCK;
			SysTickConfig.u32ReloadValue = 1600000;
			SysTickConfig.u8Interrupt = SYSTICK_INTERRUPT_ENABLED;
			break;
	}
	
}


u8 SCHEDULER_u8AddTask(void (*ptrF) (void),u8 u8Delay, u8 u8Period)
{
	u8 u8TaskIndex = 0;
	while (SCHEDULER_tasksArr[u8TaskIndex]->ptrF != 0 & u8TaskIndex < SCHEDULER_MAX_TASKS)
	{
		u8TaskIndex++;
	}
	if (u8TaskIndex == SCHEDULER_MAX_TASKS)
	{
		return SCHEDULER_MAX_TASKS;
	}
	else
	{
		SCHEDULER_tasksArr[u8TaskIndex]->ptrF = prtF;
		SCHEDULER_tasksArr[u8TaskIndex]->u8Delay = u8Delay;
		SCHEDULER_tasksArr[u8TaskIndex]->u8Period = u8Period;
		SCHEDULER_tasksArr[u8TaskIndex]->u8RunSignalFlag = SCHEDULER_SIGNAL_NOT_RUNNING;
		return u8TaskIndex;
	}
}


u8 SCHEDULER_vidStartScheduling(void)
{
	SysTick_vidStart();
}

/*Doesn't execute the tasks, but calculates the time when then should run.*/
void SCHEDULER_vidUpdate(void)
{
	u8 u8TaskIndex = 0;
	for (u8TaskIndex = 0; u8TaskIndex < SCHEDULER_MAX_TASKS; u8TaskIndex++)
	{
		if (SCHEDULER_tasksArr[u8TaskIndex]->ptrF)
		{
			if (SCHEDULER_tasksArr[u8TaskIndex]->u8Delay == 0)
			{
				SCHEDULER_tasksArr[u8TaskIndex]->u8RunSignalFlag = SCHEDULER_SIGNAL_RUN;
				SCHEDULER_tasksArr[u8TaskIndex]->u8Delay = SCHEDULER_tasksArr[u8TaskIndex]->u8Period;
			}
			else
			{
				SCHEDULER_tasksArr[u8TaskIndex]->u8Delay--;
			}
		}
	}
}

void SCHEDULER_vidDispatch(void)
{
	
}
