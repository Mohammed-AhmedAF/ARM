#ifndef _TIMER_IF_INTERFACE_H
#define _TIMER_IF_INTERFACE_H

typedef struct
{
	void (*ptrFDelayMicro) (u32);
	void (*ptrFDelayMilli) (u32);
	void (*ptrFDisableTimer) (void);
} TIMERHandle_t;

#endif