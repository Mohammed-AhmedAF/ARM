/*
 * TIMERS_private.h
 *
 *  Created on: Dec 11, 2021
 *      Author: Mohammed
 */
#ifndef _TIMERS_PRIVATE_H_
#define _TIMERS_PRIVATE_H_

typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RCR;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t BDTR;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
}AdvancedTimer_t;

typedef struct
{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SMCR;
	uint32_t DIER;
	uint32_t SR;
	uint32_t EGR;
	uint32_t CCMR1;
	uint32_t CCMR2;
	uint32_t CCER;
	uint32_t CNT;
	uint32_t PSC;
	uint32_t ARR;
	uint32_t CCR1;
	uint32_t CCR2;
	uint32_t CCR3;
	uint32_t CCR4;
	uint32_t DCR;
	uint32_t DMAR;
}GPTM_t;

typedef struct
{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t DIER;
	uint32_t SR;
	uint32_t EGR;
	uint32_t CNT;
	uint32_t PSC;
	uint32_t APR;
} BasicTimer_t;

/*Advanced timers*/
#define TIM1 ((AdvancedTimer_t*) 0x40012C00)
#define TIM8 ((AdvancedTimer_t*) 0x40013400)

/*General purpose timers*/
#define TIM2 ((GPTM_t*) 0x40000000)
#define TIM3 ((GPTM_t*) 0x40000400)
#define TIM4 ((GPTM_t*) 0x40000800)
#define TIM5 ((GPTM_t*) 0x40000C00)

/*General purpose timers*/
#define TIM9 ((Timer_Type*) 0x40014C00)
#define TIM10 ((Timer_Type*) 0x40015000)
#define TIM11 ((Timer_Type*) 0x40015400)
#define TIM12 ((Timer_Type*) 0x40001800)
#define TIM13 ((Timer_Type*) 0x40001C00)
#define TIM14 ((Timer_Type*) 0x40002000)

/*Basic timer*/
#define TIM6 ((BasicTimer_t *) 0x40001000))
#define TIM7 ((BasicTimer_t *) 0x40001400))


#endif /* SRC_TIMERS_PRIVATE_H_ */
