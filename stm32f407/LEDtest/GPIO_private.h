#ifndef _GPIO_PRIVATE_H
#define _GPIO_PRIVATE_H

typedef struct {
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;
} GPIO_Type;

#define GPIO_PORTA ((GPIO_Type*) 0x40020000)
#define GPIO_PORTB ((GPIO_Type*) 0x40020400)
#define GPIO_PORTC ((GPIO_Type*) 0x40020800)
#define GPIO_PORTD ((GPIO_Type*) 0x40020C00)
#define GPIO_PORTE ((GPIO_Type*) 0x40021000)
#define GPIO_PORTF ((GPIO_Type*) 0x40021400)

#endif
