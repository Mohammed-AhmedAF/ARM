#include "STD_TYPES.h"
#include "Macros.h"
#include "SPI_private.h"
#include "SPI_interface.h"
#include "GPIO_interface.h"

void SPI_vidInit(void)
{
	/*Ensuring that SSE is cleared before any configuration is done*/
	SSICR1 = 0;  
	/*Selecting clock source*/
	SSICC = 0;
	
	/*Selecting prescaler*/
	SSICPSR = 4;
	
	SSICR0 = 0x00007;
	
	/*Enable SSI*/
	SET_BIT(SSICR1,1);
	
}

void SPI_vidSendByte(u8 u8Byte)
	
{
	GPIO_vidSetPinValue(GPIO_PORTD,GPIO_PIN1,STD_LOW);
	while(GET_BIT(SSISR,1) == 0);
	SSIDR = u8Byte;
	while(GET_BIT(SSISR,4) == 1);
	GPIO_vidSetPinValue(GPIO_PORTD,GPIO_PIN1,STD_HIGH);
	
}