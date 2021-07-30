#include "Macros.h"
#include "STD_TYPES.h"
#include "SYSCNTRL_interface.h"
#include "TIMERS_interface.h"
#include "GPIO_interface.h"
#include "SysTick_interface.h"
#include "SCHEDULER_interface.h"


static sTask_t SCHEDULER_tasksArr[SCHEDULER_MAX_TASKS];
static TIMERConfig_t timer0AConfig;
SysTickConfig_t SysTickConfig;


void SCHEDULER_vidInit(u8 u8TickSource)	
{
	switch(u8TickSource)
	{
		case SCHEDULER_TICKSOURCE_TIMER0:
		SYSCNTRL_vidEnableTimerClock(SYSCNTRL_TIMER_0);
		timer0AConfig.ptrFunc = SCHEDULER_vidUpdate;
		timer0AConfig.u16ReloadValue = 16000;
		timer0AConfig.u8Config = TIMER_CONFIG_1632_16BIT;
		timer0AConfig.u8TimerACountDir = TIMER_TIMERA_COUNTDIR_DOWN;
		timer0AConfig.u8TimerAMode = TIMER_TIMERA_MODE_PERIODIC;
		timer0AConfig.u8InterruptMask = TIMER_TIMERA_INTERRUPT_TIMEOUT;
		break;
		case SCHEDULER_TICKSOURCE_SYSTICK:

			SysTick_vidInit(SYSTICK_SYSTEM_CLOCK,SYSTICK_INTERRUPT_ENABLED);
			SysTick_vidSetValue(160000);
			SysTick_vidPutISR(SCHEDULER_vidUpdate);
			SysTick_vidStart();
			break;
	}
	
}


u8 SCHEDULER_u8AddTask(void (*ptrF) (void),u8 u8Delay, u8 u8Period)
{
	u8 u8TaskIndex = 0;
	while ((SCHEDULER_tasksArr[u8TaskIndex].u8TaskDefined != 0) && (u8TaskIndex < SCHEDULER_MAX_TASKS))
	{
		u8TaskIndex++;
	}
	
	if (u8TaskIndex == SCHEDULER_MAX_TASKS)
	{
		return SCHEDULER_MAX_TASKS;
	}

		SCHEDULER_tasksArr[u8TaskIndex].ptrF = ptrF;
		SCHEDULER_tasksArr[u8TaskIndex].u8Delay = u8Delay;
		SCHEDULER_tasksArr[u8TaskIndex].u8Period = u8Period;
		SCHEDULER_tasksArr[u8TaskIndex].u8RunSignalFlag = SCHEDULER_SIGNAL_NOT_RUNNING;
		SCHEDULER_tasksArr[u8TaskIndex].u8TaskDefined = 1;
		return u8TaskIndex;
}


void SCHEDULER_vidStartScheduling(void)
{
	SysTick_vidStart();

}

/*Doesn't execute the tasks, but calculates the time when then should run.*/
void SCHEDULER_vidUpdate(void)
{
	u8 u8TaskIndex = 0;
	for (u8TaskIndex = 0; u8TaskIndex < SCHEDULER_MAX_TASKS; u8TaskIndex++)
	{

		if (SCHEDULER_tasksArr[u8TaskIndex].u8TaskDefined == 1)
		{
			if (SCHEDULER_tasksArr[u8TaskIndex].u8Delay == 0)
			{

				SCHEDULER_tasksArr[u8TaskIndex].u8RunSignalFlag = SCHEDULER_SIGNAL_RUN;
				SCHEDULER_tasksArr[u8TaskIndex].u8Delay = SCHEDULER_tasksArr[u8TaskIndex].u8Period;
			}
			else
			{
				SCHEDULER_tasksArr[u8TaskIndex].u8Delay--;
			}
		}
	}
}

void SCHEDULER_vidDispatch(void)
{
	u8 u8TaskIndex;
	for (u8TaskIndex = 0; u8TaskIndex < SCHEDULER_MAX_TASKS; u8TaskIndex++)
	{
		if (SCHEDULER_tasksArr[u8TaskIndex].u8RunSignalFlag == SCHEDULER_SIGNAL_RUN)
		{
			SCHEDULER_tasksArr[u8TaskIndex].ptrF();
			SCHEDULER_tasksArr[u8TaskIndex].u8RunSignalFlag = SCHEDULER_SIGNAL_NOT_RUNNING;
		}
	
	}
}
