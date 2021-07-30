#ifndef _SCHEDULER_INTERFACE_H
#define _SCHEDULER_INTERFACE_H

#define SCHEDULER_MAX_TASKS 10

#define SCHEDULER_SIGNAL_RUN 1
#define SCHEDULER_SIGNAL_NOT_RUNNING 2

#define SCHEDULER_TICKSOURCE_TIMER0 1
#define SCHEDULER_TICKSOURCE_SYSTICK 2

typedef struct
{
	void (*ptrF) (void);
	u8 u8Delay;
	u8 u8Period;
	u8 u8RunSignalFlag;
	u8 u8TaskDefined;

} sTask_t;

void SCHEDULER_vidInit(u8 u8TickSource);
u8 SCHEDULER_u8AddTask(void (*ptrF) (void),u8 u8Delay,u8 u8Period);
void SCHEDULER_vidUpdate(void);
void SCHEDULER_vidDispatch(void);
void SCHEDULER_vidStartScheduling(void);

#endif