#include "Macros.h"
#include "STD_TYPES.h"
#include "SYSCNTRL_interface.h"
#include "GPIO_interface.h"
#include "TIMER0_interface.h"
#include "TM1637_interface.h"
#include "NVIC_interface.h"

/*Add TivaWare to make this project work*/

static volatile u32 u32OVFCnt = 0;
static volatile u32 u32Seconds = 0;
void vidCount(void);
void vidButtonHandler(void);

void vidCount(void)
{
	u32OVFCnt++;

	if (u32OVFCnt == 400)
	{
		u32Seconds++;
		TM1637_vidDisplayDecimal(u32Seconds,TM1637_SEPARATOR_DISABLED);
		u32OVFCnt = 0;
	}
}

void vidButtonHandler(void)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
	GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN4);
}

int main(void)
{
	/*Running clock for used peripherals*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	
	/*Configuring GPIO pins of on-board LEDs for testing*/
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_DIR_OUTPUT);

	/*Configuring GPIO pins of on-board buttons*/
	GPIO_vidUnlock(GPIO_PORTF);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN4);
	GPIOConfig_t strctSWRight;
	strctSWRight.u8DigEnable = GPIO_DEN_SET;
	strctSWRight.u8Direction = GPIO_DIR_INPUT;
	strctSWRight.u8PullUpRes = GPIO_PUR_ENABLED;
	strctSWRight.u8Port = GPIO_PORTF;
	strctSWRight.u8Pin = GPIO_PIN4;
	GPIO_vidConfigurePin(&strctSWRight);
	GPIO_vidLock(GPIO_PORTF);
		
	ExtInterruptConfig_t strctExtIntSWRight;
	strctExtIntSWRight.ptrFunc = vidButtonHandler;
	strctExtIntSWRight.u8BothEdges = GPIO_INTERRUPT_EVENTCONTROLLED;
	strctExtIntSWRight.u8InterruptEvent = GPIO_EVENT_FE;
	strctExtIntSWRight.u8InterruptSense = GPIO_SENSE_EDGE;
	strctExtIntSWRight.u8PullResistance = GPIO_PUR_ENABLED;
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN4,&strctExtIntSWRight);
	
	/*Initiating TM1637*/
	TM1637_vidInit();

	TIMER0_vidPutISRFunction(vidCount);
	TIMER0_vidInit(4000,1);
	
	/*NVIC control*/
	NVIC_vidSetInterrupt(NVIC_GPIOF);
	NVIC_vidSetPriority(NVIC_GPIOF,1);
	while(1)
	{
		
	}
}