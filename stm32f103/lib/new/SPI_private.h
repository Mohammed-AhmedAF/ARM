#ifndef _SPI_PRIVATE_H
#define _SPI_PRIVATE_H
#define SPI1_CR1 * ((u32*) 0x40013000)
#define SPI1_CR2 * ((u32*) 0x40013004)
#define SPI1_SR * ((u32*) 0x40013008)
#define SPI1_DR * ((u32*) 0x4001300C)
#define SPI1_CRCPR * ((u32*) 0x40013010)
#define SPI1_RXCRCR * ((u32*) 0x40013014)
#define SPI1_TXCRCR * ((u32*) 0x40013018)
#define SPI1_I2SCFGR * ((u32*) 0x4001301C)
#define SPI1_I2SPR * ((u32*) 0x40013020)
#endif