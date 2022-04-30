#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "SCHEDULER_interface.h"
#include "TM4C123.h"                    // Device header

void vidBlinkRed(void);
void vidBlinkGreen(void);

void vidBlinkRed(void)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
}

void vidBlinkGreen(void)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN2);

}

int main(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);
	
	SCHEDULER_vidInit(SCHEDULER_TICKSOURCE_TIMER0);
	
	SCHEDULER_u8AddTask(vidBlinkRed,50,200);
	SCHEDULER_u8AddTask(vidBlinkGreen,50,100);
	SCHEDULER_vidStartScheduling();
	
	while(1)
	{
		SCHEDULER_vidDispatch();
	};
}
