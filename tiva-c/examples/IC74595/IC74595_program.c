#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "IC74595_interface.h"
#include "SPI_interface.h"

static void Delay_ms(int time_ms);


void IC74595_vidInit(IC74595Config_t * IC74595Config)
{
	/*Pin direction*/
	GPIO_vidSetPinDirection(IC74595Config->u8LatchPort,IC74595Config->u8LatchPin,GPIO_OUTPUT);
	GPIO_vidSetPinDirection(IC74595Config->u8OutEnPort,IC74595Config->u8OutEnPin,GPIO_OUTPUT);
	GPIO_vidSetPinDirection(IC74595Config->u8ClearPort,IC74595Config->u8ClearPin,GPIO_OUTPUT);

	/*Pin digital enable*/
	GPIO_vidSetPinDigEnable(IC74595Config->u8LatchPort,IC74595Config->u8LatchPin,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(IC74595Config->u8OutEnPort,IC74595Config->u8OutEnPin,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(IC74595Config->u8ClearPort,IC74595Config->u8ClearPin,GPIO_DEN_SET);

	
}

void IC74595_vidClear(IC74595Config_t * config)
{
	GPIO_vidSetPinValue(config->u8ClearPin,config->u8ClearPin,STD_LOW);
	Delay_ms(200);
	GPIO_vidSetPinValue(config->u8ClearPin,config->u8ClearPin,STD_HIGH);


}

void IC74595_vidControl(IC74595Config_t * config)
{
		//GPIO_vidSetPinValue(config->u8OutEnPin,config->u8OutEnPin,STD_HIGH);
		GPIO_vidSetPinValue(config->u8LatchPort,config->u8LatchPin,STD_LOW);
		GPIO_vidSetPinValue(config->u8LatchPort,config->u8LatchPin,STD_HIGH);
		GPIO_vidSetPinValue(config->u8OutEnPin,config->u8OutEnPin,STD_LOW);

}

void IC74595_vidTest(IC74595Config_t * config, u8 u8Byte)
	
{

		GPIO_vidSetPinValue(config->u8LatchPort,config->u8LatchPin,STD_LOW);
		SPI_vidSendByte(u8Byte);
		GPIO_vidSetPinValue(config->u8LatchPort,config->u8LatchPin,STD_HIGH);
}

static void Delay_ms(int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  /* excute NOP for 1ms */
}