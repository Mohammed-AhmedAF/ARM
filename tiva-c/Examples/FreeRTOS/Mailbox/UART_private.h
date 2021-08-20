#ifndef _UART_PRIVATE_H
#define _UART_PRIVATE_H

#define UART0_IBRD * ((u32*) 0x4000C024)
#define UART0_FBRD * ((u32*) 0x4000C028)
#define UART0_CTL * ((u32*) 0x4000C030)
#define UART0_LCRH * ((u32*) 0x4000C02C)
#define UART0_DATA * ((u32*) 0x4000C000)
#define UART0_FR * ((u32*) 0x4000C018)
#define UART0_CC * ((u32*) 0x4000C000)
#define UART0_ICR * ((u32*) 0x4000C044)
#define UART0_IM * ((u32*) 0x4000C038)

#define UART1_IBRD * ((u32*) 0x4000D024)
#define UART1_FBRD * ((u32*) 0x4000D028)
#define UART1_CTL * ((u32*) 0x4000D030)
#define UART1_LCRH * ((u32*) 0x4000D02C)
#define UART1_DATA * ((u32*) 0x4000D000)
#define UART1_FR * ((u32*) 0x4000D018)
#define UART1_CC * ((u32*) 0x4000D000)

#endif

