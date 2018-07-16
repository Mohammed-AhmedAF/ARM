#ifndef _MDIO_PRIVATE_H
#define _MDIO_PRIVATE_H

#define GPIOA_ODR *((u32*) 0x4001080C)
#define GPIOB_ODR *((u32*) 0x40010C0C)
#define GPIOC_ODR *((u32*) 0x4001100C)

#define GPIOA_IDR *((u32*) 0x4001088H)
#define GPIOB_IDR *((u32*) 0x40010C8H)
#define GPIOC_IDR *((u32*) 0x4001108H)

#define GPIOA_CRL *((u32*) 0x40010800)
#define GPIOA_CRH *((u32*) 0x40010804)

#define GPIOB_CRL *((u32*) 0x40010C00)
#define GPIOB_CRH *((u32*) 0x40010C04)

#define GPIOC_CRL *((u32*) 0x40011000)
#define GPIOC_CRL *((u32*) 0x4001100C)


#endif
