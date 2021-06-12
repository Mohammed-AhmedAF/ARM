#ifndef _MDIO_INTERFACE_H
#define _MDIO_INTERFACE_H

void MDIO_vidInit(void);
void MDIO_vidSetPinConfiguration(u8 u8PortNumCpy, u8 u8PinNumCpy, u8 ConfigCpy);
void MDIO_vidSetPinMode(u8 u8PortNumCpy, u8 u8PinNumCpy, u8 u8ConfigCpy);
void MDIO_vidSetPinValue(u8 u8PortNum, u8 u8PinNum, u8 u8Value);
u8 MDIO_u8GetPinValue(u8 u8PortNum, u8 u8PinNum);
void MDIO_vidTogglePin(u8 u8Port, u8 u8Pin);

#define MDIO_PORTA 0
#define MDIO_PORTB 1
#define MDIO_PORTC 2

#define MDIO_PIN0 0
#define MDIO_PIN1 1
#define MDIO_PIN2 2
#define MDIO_PIN3 3
#define MDIO_PIN4 4
#define MDIO_PIN5 5
#define MDIO_PIN6 6
#define MDIO_PIN7 7
#define MDIO_PIN8 8
#define MDIO_PIN9 9
#define MDIO_PIN10 10
#define MDIO_PIN11 11
#define MDIO_PIN12 12
#define MDIO_PIN13 13
#define MDIO_PIN14 14
#define MDIO_PIN16 15

#define MDIO_GPOUT_PP 0
#define MDIO_GPOUT_OD 1
#define MDIO_AFOUT_PP 2
#define MDIO_AFOUT_OD 3

#define MDIO_OUTSPEED_10 0
#define MDIO_OUTSPEED_2 1
#define MDIO_OUTSPEED_50 2
#define MDIO_INPUTMODE 3


#endif
