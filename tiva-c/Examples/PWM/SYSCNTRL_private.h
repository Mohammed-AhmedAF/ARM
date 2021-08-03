#ifndef _SYSCNTRL_PRIVATE_H_
#define _SYSCNTRL_PRIVATE_H_

#define RCC * ((u32 *) 0x400F0E060)
#define RCGCGPIO *((u32 *) 0x400FE608)
#define RCGCUART *((u32 *) 0x400FE618)
#define GPIOHBCTL * ((u32*) 0x400FE06C)
#define RCGCI2C * ((u32*) 0x400FE620)
#define RCGCADC * ((u32*) 0x400FE638)
#define RCGCTIMER * ((u32 *) 0x400FE604)
#define RCGCPWM * ((u32*) 0x400FE640)

#endif
