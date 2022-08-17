#include "Macros.h"
#include "STD_TYPES.h"
#include "SYSCNTRL_interface.h"
#include "GPIO_interface.h"
#include "APP_interface.h"

void APP_LED_vidInit(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	
	/*GPIO configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DEN_SET);
}

void APP_LED_vidToggle(void)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);
}