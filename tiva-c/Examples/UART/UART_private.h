#ifndef _UART_PRIVATE_H
#define _UART_PRIVATE_H

#define UART0_IBRD * ((u32*) 0x4000C024)
#define UART0_FBRD * ((u32*) 0x4000C028)
#define UART0_CTL * ((u32*) 0x4000C030)
#define UART0_LCRH * ((u32*) 0x4000C02C)
#define UART0_DATA * ((u32*) 0x4000C000)
#define UART0_FR * ((u32*) 0x4000C018)
#define UART0_CC * ((u32*) 0x4000C000)

#endif