#ifndef _TIMERS_PRIVATE_H
#define _TIMERS_PRIVATE_H

/*GPTM0 registers definitions*/
#define GPTM0_CFG * ((u32*) 0x40030000)
#define GPTM0_TAMR * ((u32*) 0x40030004)
#define GPTM0_TBMR * ((u32*) 0x40030008)
#define GPTM0_CTL * ((u32*) 0x4003000C)
#define GPTM0_SYNC * ((u32*) 0x40030010)
#define GPTM0_IMR * ((u32*) 0x40030018)
#define GPTM0_RIS * ((u32*) 0x4003001C)
#define GPTM0_MIS * ((u32*) 0x40030020)
#define GPTM0_ICR * ((u32*) 0x40030024)
#define GPTM0_TAILR * ((u32*) 0x40030028)
#define GPTM0_TBILR * ((u32*) 0x4003002C)
#define GPTM0_TAMATCHR * ((u32*) 0x40030030)
#define GPTM0_TBMATCHR * ((u32*) 0x40030034)
#define GPTM0_TAPR * ((u32*) 0x40030038)
#define GPTM0_TBPR * ((u32*) 0x4003003C)
#define GPTM0_TAPMR * ((u32*) 0x40030040)
#define GPTM0_TBPMR * ((u32*) 0x40030044)
#define GPTM0_TAR * ((u32*) 0x40030048)
#define GPTM0_TBR * ((u32*) 0x4003004C)
#define GPTM0_TAV * ((u32*) 0x40030050)
#define GPTM0_TBV * ((u32*) 0x40030054)
#define GPTM0_RTCPD * ((u32*) 0x40030058)
#define GPTM0_TAPS * ((u32*) 0x4003005C)
#define GPTM0_TBPS * ((u32*) 0x40030060)
#define GPTM0_TAPV * ((u32*) 0x40030064)
#define GPTM0_TBPV * ((u32*) 0x40030068)
#define GPTM0_PP * ((u32*) 0x40030FC0)

#endif
