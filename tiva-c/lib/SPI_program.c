#include "STD_TYPES.h"
#include "Macros.h"
#include "SPI_private.h"
#include "SPI_interface.h"
#include "GPIO_interface.h"

void SPI_vidInit(SPIConfig_t *SPIConfig)
{
	/*Ensuring that SSE is cleared before any configuration is done*/
	SSICR1 = 0;
	/*Selecting clock source*/
	switch (SPIConfig->u8ClockSource)
	{
	case SPI_CLOCKSOURCE_SYSTEM_CLOCK:
		SSICC = 0;
		break;
	case SPI_CLOCKSOURCE_PIOSC:
		SSICC = 0x5;
		break;
	}

	/*Selecting prescaler*/
	SSICPSR = SPIConfig->u8Prescaler;

	/*Selecting Master/Slave*/
	switch (SPIConfig->u8Mode)
	{
	case SPI_MODE_MASTER:
		CLEAR_BIT(SSICR1, 2);
		break;
	case SPI_MODE_SLAVE:
		SET_BIT(SSICR1, 2);
		break;
	}

	/*Data size*/
	switch (SPIConfig->u8DataSize)
	{
	case SPI_DATASIZE_8BITS:
		SSICR0 = 0x00007;
		break;
	case SPI_DATASIZE_9BITS:
		SSICR0 = 0x00008;
		break;
	}

	/*Enable SSI*/
	SET_BIT(SSICR1, 1);
}

void SPI_vidSendByte(u8 u8Byte)
{

	GPIO_vidSetPinValue(GPIO_PORTD, GPIO_PIN1, STD_LOW);
	while (GET_BIT(SSISR, 1) == 0)
		;
	SSIDR = u8Byte; /* transmit byte over SSI1Tx line */
	while (GET_BIT(SSISR, 4) == 1 & GET_BIT(SSISR, 1) == 0)
		;
	GPIO_vidSetPinValue(GPIO_PORTD, GPIO_PIN1, STD_HIGH);
}
