#ifndef _BUTTON_INTERFACE_H
#define _BUTTON_INTERFACE_H

typedef struct
{
	u8 u8Port;
	u8 u8Pin;
}ButtonConfig_t;

typedef enum {
BUTTON_UP, BUTTON_DOWN, BUTTON_PRESSED, BUTTON_RELEASED
}ButtonState_t;
void delay_ms(int milli);
ButtonState_t Button_u8GetButtonDebounced(ButtonConfig_t * buttonConfig,
	ButtonState_t buttonState);


#endif