#ifndef _SYSTICK_PRIVATE_H
#define _SYSTICK_PRIVATE_H

typedef struct {
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
	u32 CALIB;

}SysTick_Type;

#define STK ((SysTick_Type*) 0xE000E010)

#endif
