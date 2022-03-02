/*
 Button Debouncing driver based on code from
 https://hackaday.com/2015/12/09/embed-with-elliot-debounce-your-noisy-buttons-part-i/
*/

#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "BUTTON_interface.h"


void delay_ms(int milli)
{
	for (int i = 0; i < milli; i++)
	{
		for (int j = 0; j < 3118; j++)
		{
		
		}
	}
}

/*Button debouned function; assuming the pin is pulled-up*/
enum ButtonState Button_u8GetButtonDebounced(enum ButtonState buttonState)
{
	/*If button is pressed*/
	if (GPIO_u8GetPinValue(GPIO_PORTA,GPIO_PIN5) == STD_LOW)
	{
	if (buttonState == BUTTON_PRESSED)
	{
		buttonState = BUTTON_DOWN;
	}
	if (buttonState == BUTTON_UP)
	{
		delay_ms(5);
		if (GPIO_u8GetPinValue(GPIO_PORTA,GPIO_PIN5) == STD_LOW)
		{
			buttonState = BUTTON_PRESSED;
		}			
	}
	}
	/*If button is not released*/
	else
	{
		if (buttonState == BUTTON_RELEASED)
		{
			buttonState = BUTTON_DOWN;
		}
		if (buttonState == BUTTON_DOWN)
		{
			if (GPIO_u8GetPinValue(GPIO_PORTA,GPIO_PIN5) == STD_HIGH)
			{
				delay_ms(5);
				if (GPIO_u8GetPinValue(GPIO_PORTA,GPIO_PIN5) == STD_HIGH)
				{
					buttonState = BUTTON_UP;
				}
			}
		}
	}
	return buttonState;
}