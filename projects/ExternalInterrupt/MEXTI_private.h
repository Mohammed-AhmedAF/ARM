#ifndef _MEXTI_PRIVATE_H
#define _MEXTI_PRIVATE_H

typedef struct {
	u32 IMR;
	u32 EMR;
	u32 RTSR;
	u32 FTSR;
	u32 SWIER;
	u32 PR;
}EXTI_Type;

#define MEXTI ((volatile EXTI_Type*) 0x40010400)

#endif
