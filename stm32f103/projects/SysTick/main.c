#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MDIO_interface.h"
#include "MRCC_interface.h"
#include "MSTK_interface.h"

void vidBlink(void)
{
	MDIO_vidTogglePin(MDIO_PORTA,MDIO_PIN0);
}

/*STM32 blue pill example*/
void main(void) {
	
MRCC_vidInit();
	MRCC_vidEnableClock(BUS_APB2,PERIPHERAL_GPIOA);
	
	MDIO_vidInit();
	MDIO_vidSetPinConfiguration(MDIO_PORTA,MDIO_PIN0,MDIO_GPOUT_PP);
	MDIO_vidSetPinValue(MDIO_PORTA,MDIO_PIN0,STD_HIGH);
	
	MSTK_vidInit();
	MSTK_vidSetCallBack(vidBlink);
	
	while(1);	
}
