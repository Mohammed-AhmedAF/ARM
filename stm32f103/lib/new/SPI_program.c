#include "Macros.h"
#include "STD_TYPES.h"
#include "SPI_private.h"
#include "SPI_interface.h"
#include "stm32f10x.h"                  // Device header

void SPI_vidInit(SPIConfig_t * config)
{
	/*Configuration*/
	switch(config->u8Config)
	{
		case SPI_CONFIG_MASTER:
			SPI1->CR1 |= 0x4; // Master Mode
			break;
		case SPI_CONFIG_SLAVE:
			CLEAR_BIT(SPI1->CR1,2);
			break;
	}
	
	/*Baudrate selection*/
	switch(config->u8BaudrateControl)
	{
		case SPI_BAUDRATE_DIV_2:
			SPI1->CR1 |= 0<<3;
			break;
		case SPI_BAUDRATE_DIV_4:
			SPI1->CR1 |= 1<<3;
			break;
		case SPI_BAUDRATE_DIV_8:
			SPI1->CR1 |= 2<<3;
			break;
		case SPI_BAUDRATE_DIV_16:
			SPI1->CR1 |= 3<<3; // fclk / 16
			break;
		case SPI_BAUDRATE_DIV_32:
			SPI1->CR1 |= 4<<3; // fclk / 32
			break;
		case SPI_BAUDRATE_DIV_64:
			SPI1->CR1 |= 5<<3; // fclk / 64
			break;
		case SPI_BAUDRATE_DIV_128:
			SPI1->CR1 |= 6<<3; // fclk / 128
			break;
		case SPI_BAUDRATE_DIV_256:
			SPI1->CR1 |= 7<<3; // fclk / 265
			break;
	}

	/*Clock polarity*/
	switch(config->u8ClockPolarity)
	{
		case SPI_CLK_POLARITY_0:
			CLEAR_BIT(SPI1->CR1,1);
			break;
		case SPI_CLK_POLARITY_1:
			SET_BIT(SPI1->CR1,1);
			break;
	}
	
	/*Frame format*/
	switch(config->u8FrameFormat)
	{
		case SPI_FRAMEFORMAT_LSB:
			SET_BIT(SPI1_CR1,7);
			break;
		case SPI_FRAMEFORMAT_MSB:
			CLEAR_BIT(SPI1_CR1,7);
			break;
	}
	
	/*SS enabled*/
	SPI1->CR2 |= 0x4;
	
	/*SPI enabled*/
	SET_BIT(SPI1->CR1,6); 

	/*Enabling SPI*/
	SPI1->CR1 |= 0x40; 	

}

void SPI_vidTransmitByte(u8 u8Byte)
{
	/*Wait while transmit buffer empty turns to 1*/
	while((GET_BIT(SPI1_SR,7) == 1));
	
	SPI1_DR = u8Byte;
	
	
}