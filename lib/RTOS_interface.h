#ifndef _RTOS_INTERFACE_H
#define _RTOS_INTERFACE_H

typedef struct {
	void (*TaskHandler) (void);
	u16 Periodicity;
}Task;

void RTOS_vidInit(void);
void RTOS_vidCreateTask(u8 ID, u16 Period, void (*ptrFunc)(void));

#endif
