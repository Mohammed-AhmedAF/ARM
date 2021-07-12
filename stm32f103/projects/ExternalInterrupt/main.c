#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MDIO_interface.h"
#include "MRCC_interface.h"
#include "MNVK_interface.h"
#include "MEXTI_interface.h"

void func0(void);
void func1(void);

void func0(void) {
		DIO_vidTogglePin(MDIO_PORTB,MDIO_PIN0);
}

void func1(void)
{
		DIO_vidTogglePin(MDIO_PORTB,MDIO_PIN1);

}

int main(void) {
	MRCC_vidInit();
	MRCC_vidEnableClock(BUS_APB2,PERIPHERAL_GPIOA); /*To enable clock for input pin*/
	MRCC_vidEnableClock(BUS_APB2,PERIPHERAL_GPIOB);

	MRCC_vidEnableClock(BUS_APB2,PERIPHERAL_AFIO); /*To enable clock for external interrupt*/

	MDIO_vidInit();

	MDIO_vidSetPinConfiguration(MDIO_PORTA,MDIO_PIN0,MDIO_AFOUT_PP);
	MDIO_vidSetPinMode(MDIO_PORTA,MDIO_PIN0,MDIO_INPUTMODE);
	MDIO_vidSetPinValue(MDIO_PORTA,MDIO_PIN0,STD_HIGH); /*To make it pull up*/
	
	MDIO_vidSetPinConfiguration(MDIO_PORTA,MDIO_PIN1,MDIO_AFOUT_PP);
	MDIO_vidSetPinMode(MDIO_PORTA,MDIO_PIN1,MDIO_INPUTMODE);
	MDIO_vidSetPinValue(MDIO_PORTA,MDIO_PIN1,STD_HIGH); /*To make it pull up*/
	
	/*Configuration  for LED0*/
	MDIO_vidSetPinMode(MDIO_PORTB,MDIO_PIN0,MDIO_OUTSPEED_10);
	MDIO_vidSetPinConfiguration(MDIO_PORTB,MDIO_PIN0,MDIO_GPOUT_PP);
	MDIO_vidSetPinValue(MDIO_PORTB,MDIO_PIN0,STD_LOW);

	/*Configuration for LED1*/
	MDIO_vidSetPinMode(MDIO_PORTB,MDIO_PIN1,MDIO_OUTSPEED_10);
	MDIO_vidSetPinConfiguration(MDIO_PORTB,MDIO_PIN1,MDIO_GPOUT_PP);
	MDIO_vidSetPinValue(MDIO_PORTB,MDIO_PIN1,STD_LOW);

	/*External interrupt 0*/
	EXTI_vidSetCallback(EXTI_LINE_0,func0);
	MNVK_vidEnableInterrupt(6); /*That number is the position in page 197 of manual*/
	EXTI_vidSetEXTIMode(EXTI_LINE_0,MEXTI_MODE_FALLING);
	EXTI_vidEnable(EXTI_LINE_0);
	
	/*External interrupt 1*/
	EXTI_vidSetCallback(EXTI_LINE_1,func1);
	MNVK_vidEnableInterrupt(7); /*That number is the position in page 197 of manual*/
	EXTI_vidSetEXTIMode(EXTI_LINE_1,MEXTI_MODE_FALLING);
	EXTI_vidEnable(EXTI_LINE_1);

	while(1);
}


