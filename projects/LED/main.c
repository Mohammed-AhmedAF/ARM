#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MDIO_interface.h"
#include "MRCC_interface.h"


void main(void) {
	
	MRCC_vidInit();
	MRCC_vidEnableClock(BUS_APB2,PERIPHERAL_GPIOA);
	
	MDIO_vidInit();
	MDIO_vidSetPinConfiguration(MDIO_PORTA,MDIO_PIN0,MDIO_GPOUT_PP);
	MDIO_vidSetPinValue(MDIO_PORTA,MDIO_PIN0,STD_HIGH);
	while(1);	
}
