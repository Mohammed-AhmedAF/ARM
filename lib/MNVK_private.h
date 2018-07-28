#ifndef _MNVK_PRIVATE_H
#define _MNVK_PRIVATE_H

typedef struct {
	u32 ISER[32];
	u32 ICER[32];
	u32 ISPR[32];
	u32 ICPP[32];
	u32 IABP[32]
}NVK_TYPES;

#define MNVK(volatile NVK_Type*) 0xE000E010

#endif
