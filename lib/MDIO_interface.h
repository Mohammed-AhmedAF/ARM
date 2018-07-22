#ifndef _MDIO_INTERFACE_H
#define _MDIO_INTERFACE_H

void MDIO_vidInit(void);
void MDIO_vidSetPinValue(u8 u8PortNum, u8 u8PinNum, u8 u8Value);
void MDIO_u8GetPinValue(u8 u8PortNum, u8 u8PinNum);


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
#define MDIO_PIN15 15

#endif
