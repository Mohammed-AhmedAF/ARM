#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MDIO_interface.h"
#include "MRCC_interface.h"
#include "MRCC_private.h"
#include "MUART_interface.h"

u8 * name = "Mohamed\0";

void main(void) {
	MRCC_vidInit();
	MRCC_vidEnableClock(BUS_APB2,PERIPHERAL_GPIOA);
/*	MRCC_vidEnableClock(BUS_APB2,PERIPHERAL_UART1); */
	SET_BIT(MRCC->APB2ENR,14);
	MDIO_vidInit();

	MDIO_vidSetPinConfiguration(MDIO_PORTA,MDIO_PIN9,MDIO_AFOUT_PP);
	MDIO_vidSetPinConfiguration(MDIO_PORTA,MDIO_PIN10,MDIO_GPOUT_OD);

	MDIO_vidSetPinMode(MDIO_PORTA,MDIO_PIN9,MDIO_OUTSPEED_2);
	MDIO_vidSetPinMode(MDIO_PORTA,MDIO_PIN10,MDIO_OUTSPEED_2);

	MUART_vidInit();
	MUART_vidSendString(name);


	while(1) {
		MUART_vidSendByte('m');
	}
}
