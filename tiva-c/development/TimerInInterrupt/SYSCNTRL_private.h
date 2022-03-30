#ifndef _SYSCNTRL_PRIVATE_H_
#define _SYSCNTRL_PRIVATE_H_

#define RCGCGPIO *((u32 *) 0x400FE608)
#define RCGCUART *((u32 *) 0x400FE618)
#define RCGCSSI * ((u32 *)0x400FE61C)
#define RCGCI2C * ((u32*) 0x400FE620)
#define GPIOHBCTL * ((u32*) 0x400FE06C)
#define RCGCADC * ((u32*) 0x400FE638)
#define RCGCTIMER * ((u32 *) 0x400FE604)
#define RCGCPWM * ((u32*) 0x400FE640)
#endif
