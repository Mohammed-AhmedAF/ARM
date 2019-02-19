#ifndef _RCC_PRIVATE_H
#define _RCC_PRIVATE_H

#define RCC_CR * ((u32*) 0x40023800)
#define RCC_PLLCFGR * ((u32*) 0x40023804)
#define RCC_CIR * ((u32*) 0x40023808)
#define RCC_AHB1RSTR * ((u32*) 0x40023810)
#define RCC_AHB2RSTR * ((u32*) 0x40023814)
#define RCC_AHB3RSTR * ((u32*) 0x40023818)
#define RCC_APB1RSTR * ((u32*) 0x40023820)
#define RCC_APB2RSTR * ((u32*) 0x40023824)
#define RCC_AHB1ENR * ((u32*) 0x40023830)
#define RCC_AHB2ENR * ((u32*) 0x40023834)
#define RCC_AHB3ENR * ((u32*) 0x40023838)
#define RCC_APB1ENR * ((u32*) 0x40023840)
#define RCC_APB2ENR * ((u32*) 0x40023844)
#define RCC_AHB1LPENR * ((u32*) 0x40023850)
#define RCC_AHB2LPENR * ((u32*) 0x40023854)
#define RCC_AHB3LPENR * ((u32*) 0x40023858)
#define RCC_APB1LPENR * ((u32*) 0x40023860)
#define RCC_APB2LPENR * ((u32*) 0x40023864)
#define RCC_BDCR * ((u32*) 0x40023870)
#define RCC_CSR * ((u32*) 0x40023874)
#define RCC_SSCGR * ((u32*) 0x40023880)
#define RCC_PLLI2SCFGR * ((u32*) 0x40023884)
#define RCC_PLLSAICFGR * ((u32*) 0x40023888)
#define RCC_DCKCFGR * ((u32*) 0x4002388C)


#endif
