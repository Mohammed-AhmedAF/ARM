#ifndef _MUART_PRIVATE_H
#define _MUART_PRIVATE_H

typedef struct {
	u32 SR;
	u32 DR;
	u32 BRR;
	u32 CR1;
	u32 CR2;
	u32 CR3;
	u32 GTPR;
}UART_Type;

#define MUART ((volatile UART_Type*) 0x40013800)
#define MUART2 ((volatile UART_Type*) 0x40004400)
#define MUART3 ((volatile UART_Type*) 0x40004800)
#define MUART4 ((volatile UART_Type*) 0x40004C00)
#define MUART5 ((volatile UART_Type*) 0x40005000)
#endif
