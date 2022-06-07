#ifndef _SPI_PRIVATE_H
#define _SPI_PRIVATE_H

/*SPI0*/

/*SPI1*/
#define SSICR0 * ((u32 * const) 0x40009000)
#define SSICR1 * ((u32 * const) 0x40009004)
#define SSIDR * ((u32 * const) 0x40009008)
#define SSISR * ((u32 * const) 0x4000900C)
#define SSICPSR * ((u32 * const) 0x40009010)
#define SSICC * ((u32 * const) 0x40009FC8)
 

#endif
