#ifndef _RCC_PRIVATE_H
#define _RCC_PRIVATE_H

#define RCC * ((unsigned int *) 0x400FE060)
#define RCGC0 * ((unsigned int *) 0x400FE100)
#define RCGC2 * ((unsigned int*) 0x400FE108)
#define RCGCGPIO * ((unsigned int *) 0x400FE608)
#define RCGCTIMER * ((unsigned int *) 0x400FE604)
#define RCGCUART * ((unsigned int *) 0x400FE618)
	
#endif
