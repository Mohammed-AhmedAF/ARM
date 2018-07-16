#ifndef _MDIO_INTERFACE_H
#define _MDIO_INTERFACE_H


void MDIO_vidInit(void);
void MDIO_vidSetPinValue(u8 u8PortNum, u8 u8PinNum, u8 u8Value);
void MDIO_u8GetPinValue(u8 u8PortNum, u8 u8PinNum);

#endif
