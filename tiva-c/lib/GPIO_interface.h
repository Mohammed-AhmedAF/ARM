#ifndef _GPIO_INTERFACE_H
#define _GPIO_INTERFACE_H

void GPIO_vidSetPinValue(u8 u8PortNumCpy,u8 u8PinNumCpy, u8 u8ValueCpy);
void GPIO_vidSetPinDirection(u8 u8PortNumCpy, u8 u8PinCpy,u8 u8DirCpy);
void GPIO_vidSetPinDigEnable(u8 u8PortNumCpy, u8 u8PinCpy, u8 u8DigEnable);
void GPIO_vidTogglePin(u8 u8Port, u8 u8Pin);
void GPIO_vidConigurePUR(u8 u8Port, u8 u8Pin, u8 u8PURConfig);
void GPIO_vidSelectInterruptSense(u8 u8Port, u8 u8Pin, u8 u8Sense);
void GPIO_vidSelectAlterFunction(u8 u8PortNumCpy, u8 u8PinNumCpy);
void GPIO_vidConigurePullDown(u8 u8Port, u8 u8Pin, u8 u8PURConfig);
void GPIO_vidEnableInterrupt(u8 u8Port, u8 u8Pin);
void GPIO_vidDisableInterrupt(u8 u8Port, u8 u8Pin);


#define GPIO_PORTA 0
#define GPIO_PORTB 1
#define GPIO_PORTC 2
#define GPIO_PORTD 3
#define GPIO_PORTE 4
#define GPIO_PORTF 5

#define GPIO_PIN0 0
#define GPIO_PIN1 1
#define GPIO_PIN2 2
#define GPIO_PIN3 3
#define GPIO_PIN4 4
#define GPIO_PIN5 5
#define GPIO_PIN6 6
#define GPIO_PIN7 7

#define GPIO_INPUT 0
#define GPIO_OUTPUT 1

#define GPIO_DEN_SET 1
#define GPIO_DEN_CLEAR 0

#define GPIO_PUR_DISABLED 0
#define GPIO_PUR_ENABLED 1

#define GPIO_PDR_DISABLED 0
#define GPIO_PDR_ENABLED 1

#define GPIO_SENSE_EDGE 0
#define GPIO_SENSE_LEVEL 1

#endif
