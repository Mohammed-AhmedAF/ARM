#ifndef _GPIO_INTERFACE_H
#define _GPIO_INTERFACE_H

void GPIO_vidInit(void);
void GPIO_vidSetPinConfiguration(u8 u8PortNumCpy, u8 u8PinNumCpy, u8 ConfigCpy);
void GPIO_vidSetPinMode(u8 u8PortNumCpy, u8 u8PinNumCpy, u8 u8ConfigCpy);
void GPIO_vidSetPinValue(u8 u8PortNum, u8 u8PinNum, u8 u8Value);
u8 GPIO_u8GetPinValue(u8 u8PortNum, u8 u8PinNum);
void GPIO_vidTogglePin(u8 u8Port, u8 u8Pin);

#define GPIO_PORTA 0
#define GPIO_PORTB 1
#define GPIO_PORTC 2

#define GPIO_PIN0 0
#define GPIO_PIN1 1
#define GPIO_PIN2 2
#define GPIO_PIN3 3
#define GPIO_PIN4 4
#define GPIO_PIN5 5
#define GPIO_PIN6 6
#define GPIO_PIN7 7
#define GPIO_PIN8 8
#define GPIO_PIN9 9
#define GPIO_PIN10 10
#define GPIO_PIN11 11
#define GPIO_PIN12 12
#define GPIO_PIN13 13
#define GPIO_PIN14 14
#define GPIO_PIN16 15

#define GPIO_GPOUT_PP 0
#define GPIO_GPOUT_OD 1
#define GPIO_AFOUT_PP 2
#define GPIO_AFOUT_OD 3

#define GPIO_OUTSPEED_10 0
#define GPIO_OUTSPEED_2 1
#define GPIO_OUTSPEED_50 2
#define GPIO_INPUTMODE 3


#endif
