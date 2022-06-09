#ifndef _SYSTICK_PRIVATE_H
#define _SYSTICK_PRIVATE_H

typedef struct {
	u32 CTRL;
	u32 RELOAD;
	u32 CURRENT;
} SysTick_Type;

#define SysTick  ((SysTick_Type*) 0xE000E010)


#endif
