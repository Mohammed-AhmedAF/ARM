#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MSTK_interface.h"
#include "RTOS_interface.h"

/*Number of tasks*/
#define TASKSNUMBER 2/*Insert number of tasks here*/
static volatile u32 TickCount; /*Static variable that tells the current TickCount*/

Task TasksList[TASKSNUMBER];

void Scheduler(void);
void RTOS_vidInit(void) {
	MSTK_vidSetCallBack(Scheduler);
}

void RTOS_vidCreateTask(u8 IDCpy, u16 PeriodCpy, void (*ptrFunc)(void)) {
	TasksList[IDCpy].Periodicity = PeriodCpy;
	TasksList[IDCpy].TaskHandler = ptrFunc;
}

void Scheduler(void) {
	u8 LoopCounter;
	TickCount++;
	for (LoopCounter=0; LoopCounter < TASKSNUMBER; LoopCounter++) {
		if(TickCount%TasksList[LoopCounter].Periodicity == 0) {
			TasksList[LoopCounter].TaskHandler();
		}
	}
}
