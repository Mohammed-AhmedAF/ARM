#include "Macros.h"
#include "STD_TYPES.h"
#include "SPI_private.h"
#include "SPI_interface.h"
#include "stm32f10x.h"                  // Device header

void SPI_vidInit(void)
{


	/*Master-slave select*/
	SET_BIT(SPI1_CR1,2);
	
	/*SS Output enable*/
	SET_BIT(SPI1_CR2,2);
	
	/*Frequeny*/
	SET_BIT(SPI1_CR1,3);
	SET_BIT(SPI1_CR1,4);
	SET_BIT(SPI1_CR1,5);

	/*Enable SPI*/
	//SET_BIT(SPI1_CR1,6);
	
SPI1->CR1 |= 0x4; // Master Mode
SPI1->CR1 |= 0x31; // fclk / 265
SPI1->CR2 |= 0x4;
SPI1->CR1 |= 0x40; 
//	
}

void SPI_vidTransmitByte(u8 u8Byte)
{
	/*Wait while transmit buffer empty turns to 1*/
	while((GET_BIT(SPI1_SR,7) == 1));
	
	SPI1_DR = u8Byte;
	
	
}