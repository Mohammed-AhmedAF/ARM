#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "BUTTON_interface.h"

int main(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);

	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN5,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN5,GPIO_DIR_INPUT);
	GPIO_vidConfigurePUR(GPIO_PORTA,GPIO_PIN5,GPIO_PUR_ENABLED);
	
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DIR_OUTPUT);
	enum ButtonState btn5State = BUTTON_UP;
	
	
	while(1)
	{
		if (Button_u8GetButtonDebounced(btn5State) == BUTTON_PRESSED)
		{
			GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);
		}
	}
	
}