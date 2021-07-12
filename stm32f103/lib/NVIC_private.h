#ifndef _NVIC_PRIVATE_H
#define _NVIC_PRIVATE_H

typedef struct {
	u32 ISER[3];
	u32 ICER[3];
	u32 ISPR[3];
	u32 ICPR[3];
	volatile u32 IABR[3];
}NVIC_TYPE;

#define NVIC ((volatile NVIC_TYPE*) 0xE000E100)
#define AIRCR (*(volatile u32*) 0xE000E014)
#define NVIC_IPR ((volatile u8*) 0xE000E400) /*Will be used as an array*/
#define SCB_AIRCR * ((u32*) 0xE000ED0C)

#endif
