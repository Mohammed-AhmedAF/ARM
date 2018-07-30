#ifndef _MNVK_PRIVATE_H
#define _MNVK_PRIVATE_H

typedef struct {
	u32 ISER[32];
	u32 ICER[32];
	u32 ISPR[32];
	u32 ICPR[32];
	u32 IABP[32];
}NVK_Type;

#define MNVK ((volatile NVK_Type*) 0xE000E100)
#define AIRCR *(volatile u32*) 0xE000E014

#define IPR ((volatile u8*) 0x300ER00) /*the first 4 bits are reserved*/
#endif
