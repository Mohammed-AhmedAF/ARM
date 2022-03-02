#ifndef _BUTTON_INTERFACE_H
#define _BUTTON_INTERFACE_H

typedef struct
{
	u8 u8Port;
	u8 u8Pin;
}ButtonConfig_t;

enum ButtonState {BUTTON_UP, BUTTON_DOWN, BUTTON_PRESSED, BUTTON_RELEASED};
void delay_ms(int milli);
enum ButtonState Button_u8GetButtonDebounced(ButtonConfig_t * buttonConfig,
	enum ButtonState buttonState);


#endif