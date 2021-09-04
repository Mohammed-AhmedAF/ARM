#ifndef _SYSCNTRL_PRIVATE_H_
#define _SYSCNTRL_PRIVATE_H_

#define RCC * ((u32*) 0x400FE060)
#define RCC2 * ((u32*) 0x400FE070)
#define RIS * ((u32*) 0x400FE050)
#define RCGCGPIO *((unsigned int *) 0x400FE608)
#define RCGCUART *((unsigned int *) 0x400FE618)
#define RCGCSSI * ((u32 *) 0x400FE61C)
#define RCGCI2C * ((u32*) 0x400FE620)
#define RCGCTIMER * ((u32*) 0x400FE604)

#endif
