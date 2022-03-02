#ifndef _BUTTON_INTERFACE_H
#define _BUTTON_INTERFACE_H

enum ButtonState {BUTTON_UP, BUTTON_DOWN, BUTTON_PRESSED, BUTTON_RELEASED};
void delay_ms(int milli);
enum ButtonState Button_u8GetButtonDebounced(enum ButtonState buttonState);


#endif