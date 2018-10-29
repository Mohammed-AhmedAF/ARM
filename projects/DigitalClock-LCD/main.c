#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MRCC_interface.h"
#include "MDIO_interface.h"
#include "ELCD_interface.h"
#include "Clock_interface.h"
#include "MNVK_interface.h"
#include "MEXTI_interface.h"
#include "MTIM_interface.h"


void main(void) {
	/*Init*/
	MRCC_vidInit();
	MRCC_vidEnableClock(BUS_APB2,PERIPHERAL_GPIOA);
	MRCC_vidEnableClock(BUS_APB2,PERIPHERAL_GPIOB);

	/*Enable External Interrupt Clock*/
	MRCC_vidEnableClock(BUS_APB2,PERIPHERAL_AFIO);
	/*Enabling RCC clock for Timer2*/
	MRCC_vidEnableClock(BUS_APB1,PERIPHERAL_TIM2);
	MDIO_vidSetPinConfiguration(MDIO_PORTB,MDIO_PIN3,MDIO_GPOUT_PP);

	ELCD_vidInit();
	vidInitClock(); 

	/*External Interrupt used to increment hour*/
	MEXTI_vidSetEXTIMode(MEXTI_LINE0,MEXTI_MODE_IOC);
	MEXTI_vidEnable(MEXTI_LINE0);
	MEXTI_vidSetCallBack(vidIncrementHour);
	MNVK_vidEnableInterrupt(NVIC_EXTI0);

	MTIM_vidInit();

	/*Printing the clock digits befor initiating the
	  timer
	  */

	MNVK_vidEnableInterrupt(NVIC_TIM2);
	MTIM_vidPutFunction(vidCount);
	
	while(1) {
	}

}
