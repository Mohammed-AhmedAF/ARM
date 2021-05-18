#ifndef _MDIO_PRIVATE_H
#define _MDIO_PRIVATE_H

/*Output Data Registers*/
#define GPIOA_ODR *((u32*) 0x4001080C)
#define GPIOB_ODR *((u32*) 0x40010C0C)
#define GPIOC_ODR *((u32*) 0x4001100C)

/*Input Data Registers*/
#define GPIOA_IDR *((u32*) 0x4001088H)
#define GPIOB_IDR *((u32*) 0x40010C8H)
#define GPIOC_IDR *((u32*) 0x4001108H)

/*Configuration Register Low*/
#define GPIOA_CRL *((u32*) 0x40010800)
#define GPIOB_CRL *((u32*) 0x40010C00)
#define GPIOC_CRL *((u32*) 0x40011000)

/*Configuration Register High*/
#define GPIOA_CRH *((u32*) 0x40010804)
#define GPIOB_CRH *((u32*) 0x40010C04)
#define GPIOC_CRH *((u32*) 0x40011004)

/*Bit Set/Reset Register*/
#define GPIOA_BSRR *((u32*) 0x40010810)
#define GPIOB_BSRR *((u32*) 0x40010C10)
#define GPIOC_BSRR *((u32*) 0x40011010)

/*Bit Reset Register*/
#define GPIOA_BRR *((u32*) 0x40010814) 
#define GPIOB_BRR *((u32*) 0x40010C14)
#define GPIOC_BRR *((u32*) 0x40011014)

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2

typedef struct {
	u32 CRL;
	u32 CRH;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 BRR;
	u32 LCKR;
}GPIO_Type;

#define GPIOA ((GPIO_Type*) 0x40010800)
#define GPIOB ((GPIO_Type*) 0x40010C00)
#define GPIOC ((GPIO_Type*) 0x40011000)


typedef struct {
	u32 EVCR;
	u32 MAPR;
	u32 EXTICR1;
	u32 EXTICR2;
	u32 EXTICR3;
	u32 EXTICR4;
	u32 MAPR2
}AFIO_Type;

#define AFIO ((AFIO_Type*) 0x40000000)

#endif
