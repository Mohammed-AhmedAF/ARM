#ifndef _SPI_INTERFACE_H
#define _SPI_INTERFACE_H

typedef struct
{
	u8 u8Config;
	u8 u8BaudrateControl;
	u8 u8FrameFormat;
	u8 u8ClockPolarity;
	
}SPIConfig_t;

void SPI_vidInit(SPIConfig_t * config);
void SPI_vidTransmitByte(u8 u8Byte);

#define SPI_CONFIG_MASTER 1
#define SPI_CONFIG_SLAVE 0

#define SPI_CLK_POLARITY_0 0
#define SPI_CLK_POLARITY_1 1

#define SPI_FRAMEFORMAT_MSB 0
#define SPI_FRAMEFORMAT_LSB 1

#define SPI_BAUDRATE_DIV_2 0
#define SPI_BAUDRATE_DIV_4 1
#define SPI_BAUDRATE_DIV_8 2
#define SPI_BAUDRATE_DIV_16 3
#define SPI_BAUDRATE_DIV_32 4
#define SPI_BAUDRATE_DIV_64 5
#define SPI_BAUDRATE_DIV_128 6
#define SPI_BAUDRATE_DIV_256 7

#endif