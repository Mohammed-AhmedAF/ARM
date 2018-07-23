#ifndef _MRCC_INTERFACE_H
#define _MRCC_INTERFACE_H

void MRCC_vidInit(void);
void MRCC_vidEnableClock(u8 u8BusCpy, u8 u8PeripheralCpy);

#define BUS_AHB 0
#define BUS_APB1 1
#define BUS_APB2 2

#define PERIPHERAL_GPIOA 4
#define PERIPHERAL_GPIOB 8
#define PERIPHERAL_GPIOC 10

#endif
