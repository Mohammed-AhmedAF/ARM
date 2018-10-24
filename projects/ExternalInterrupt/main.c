#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MDIO_interface.h"
#include "MRCC_interface.h"
#include "MNVK_interface.h"
#include "MEXTI_interface.h"

void func(void);

void func(void) {
	static  u8 flag = 0;
	if (flag == 0) {
		MDIO_vidSetPinValue(MDIO_PORTB,MDIO_PIN0,STD_HIGH);
		flag = 1;
	}
	else {
		MDIO_vidSetPinValue(MDIO_PORTB,MDIO_PIN0,STD_LOW);
		flag = 0;
	}

}

void main(void) {
	MRCC_vidInit();
	MRCC_vidEnableClock(BUS_APB2,PERIPHERAL_GPIOA); /*To enable clock for input pin*/
	MRCC_vidEnableClock(BUS_APB2,PERIPHERAL_GPIOB);
	MRCC_vidEnableClock(BUS_APB2,PERIPHERAL_AFIO); /*To enable clock for external interrupt*/

	MDIO_vidInit();

	MDIO_vidSetPinConfiguration(MDIO_PORTA,MDIO_PIN0,MDIO_AFOUT_PP);
	MDIO_vidSetPinMode(MDIO_PORTA,MDIO_PIN0,MDIO_INPUTMODE);
	MDIO_vidSetPinValue(MDIO_PORTA,MDIO_PIN0,STD_HIGH); /*To make it pull up*/

	/*Configuration  for LED*/
	MDIO_vidSetPinMode(MDIO_PORTB,MDIO_PIN0,MDIO_OUTSPEED_10);
	MDIO_vidSetPinConfiguration(MDIO_PORTB,MDIO_PIN0,MDIO_GPOUT_PP);
	MDIO_vidSetPinValue(MDIO_PORTB,MDIO_PIN0,STD_LOW);


	MEXTI_vidSetCallBack(func);
	MNVK_vidEnableInterrupt(6); /*That number is the position in page 197 of manual*/
	MEXTI_vidSetEXTIMode(0,MEXTI_MODE_FALLING);
	MEXTI_vidEnable(0);

	while(1);
}


