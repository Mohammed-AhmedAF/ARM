#ifndef _MTIM_PRIVATE_H
#define _MTIM_PRIVATE_H

typedef struct {
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMCR;
	volatile u32 DIER;
	volatile u32 SR;
	volatile u32 EGR;
	volatile u32 CMR1;
	volatile u32 CMR2;
	volatile u32 CCER;
	volatile u32 CNT;
	volatile u32 PSC;
	volatile u32 ARR;
	volatile u32 CRR1;
	volatile u32 CCR2;
	volatile u32 CCR3;
	volatile u32 CCR4;
	volatile u32 DCR;
	volatile u32 DMAR;
}Timer_Type;

#define MTIM2 ((Timer_Type*) 0x40000000)
#define MTIM3 ((Timer_Type*) 0x40000400)
#define MTIM4 ((Timer_Type*) 0x40000800)
#define MTIM5 ((Timer_Type*) 0x40000C00)

#endif
