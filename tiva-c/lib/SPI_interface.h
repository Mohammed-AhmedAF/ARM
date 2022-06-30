#ifndef _SPI_INTERFACE_H
#define _SPI_INTERFACE_H

typedef struct
{
	u8 u8Module;
	u8 u8ClockSource;
	u8 u8DataSize;
	u8 u8Mode;
	u8 u8Prescaler;
	u8 u8InterruptMask;
	
}SPIConfig_t;

#define SPI_MODULE_0 0
#define SPI_MODULE_1 1
#define SPI_MODULE_2 2
#define SPI_MODULE_3 3

#define SPI_CLOCKSOURCE_SYSTEM_CLOCK 0
#define SPI_CLOCKSOURCE_PIOSC 1

#define SPI_DATASIZE_8BITS 8 
#define SPI_DATASIZE_9BITS 9

#define SPI_MODE_MASTER 0
#define SPI_MODE_SLAVE 1

#define SPI_INTERRUPT_TX_FIFO 1<<3
#define SPI_INTERRUPT_RX_FIFO 1<<2

void SPI_vidInit(SPIConfig_t * SPIConfig);
void SPI_vidSendByte(u8 u8Byte);

#endif