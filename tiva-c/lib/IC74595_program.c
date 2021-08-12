#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "IC74595_interface.h"

void IC74595_vidInit(IC74595Config_t * IC74595Config)
{
	/*Pin direction*/
	GPIO_vidSetPinDirection(IC74595Config->u8LatchPort,IC74595Config->u8LatchPin,GPIO_OUTPUT);
	GPIO_vidSetPinDirection(IC74595Config->u8OutEnPort,IC74595Config->u8OutEnPin,GPIO_OUTPUT);
	
	/*Pin digital enable*/
	GPIO_vidSetPinDigEnable(IC74595Config->u8LatchPort,IC74595Config->u8LatchPin,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(IC74595Config->u8OutEnPort,IC74595Config->u8OutEnPin,GPIO_DEN_SET);
}

void IC74595_vidControl(IC74595Config_t * config)
{
		GPIO_vidSetPinValue(config->u8OutEnPin,config->u8OutEnPin,STD_HIGH);
		GPIO_vidSetPinValue(config->u8LatchPort,config->u8LatchPin,STD_HIGH);
		GPIO_vidSetPinValue(config->u8LatchPort,config->u8LatchPin,STD_LOW);
		GPIO_vidSetPinValue(config->u8OutEnPin,config->u8OutEnPin,STD_LOW);

}