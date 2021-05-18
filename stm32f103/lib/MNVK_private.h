#ifndef _MNVK_PRIVATE_H
#define _MNVK_PRIVATE_H

typedef struct {
	u32 ISER[32];
	u32 ICER[32];
	u32 ISPR[32];
	u32 ICPR[32];
	u32 IABR[32];
}NVK_TYPE;

#define MNVK ((volatile NVK_TYPE*) 0xE000E100)
#define AIRCR (*(volatile u32*) 0xE000E014)
#define IPR ((volatile u8*) 0xE000E400) /*Will be used as an array*/

#endif
