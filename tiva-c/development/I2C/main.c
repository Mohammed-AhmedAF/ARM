#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "NVIC_interface.h"
#include "I2C_interface.h"

void vidBlink(void);
void vidI2C0Handler(void);

static u8 u8Message[]={'L','C','D','Q','M'};

void vidBlink(void)
{
	I2C0_vidSendMultipleBytes(u8Message,5);
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);
	GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN0);
}

void vidI2C0Handler(void)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);
	I2C0_vidClearInterrupt(I2C_INTERRUPT_RIS_ID);
}

int main(void)
{
	/*Enabling clock for used peripherals*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableI2CClock(SYSCNTRL_I2C_0);
	
	/*I2C pins GPIO configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN2);
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN3);
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN2,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN3,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN2,0x3);
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN3,0x3);
	GPIO_vidEnablePinOpenDrain(GPIO_PORTB,GPIO_PIN3);
	
	/*LED GPIO configuration*/
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_GREEN,GPIO_OUTPUT);
	
	/*Button GPIO configuration*/
	GPIO_vidUnlock(GPIO_PORTF);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN0);
	GPIO_vidLock(GPIO_PORTF);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_SWITCH2,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_SWITCH2,GPIO_INPUT);
	
	/*External interrupt configuration*/
	ExtInterruptConfig_t extInterruptConf;
	extInterruptConf.ptrFunc = vidBlink;
	extInterruptConf.u8BothEdges = GPIO_INTERRUPT_EVENTCONTROLLED;
	extInterruptConf.u8InterruptSense = GPIO_SENSE_EDGE;
	extInterruptConf.u8InterruptEvent = GPIO_EVENT_FE;
	extInterruptConf.u8PullResistance = GPIO_PUR_ENABLED;
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN0,&extInterruptConf);
	
	/*NVIC external interrupt configuration*/
	NVIC_vidSetInterrupt(NVIC_GPIOF);
	NVIC_vidSetPriority(NVIC_GPIOF,2);
	

	/*I2C Configuration*/
	I2CConfig i2cConfig;
	i2cConfig.u8Mode = I2C_MODE_MASTER;
	i2cConfig.u8TimerPeriod = 7;
	i2cConfig.u8Interrupt = I2C_INTERRUPT_RIS_ENABLED;
	i2cConfig.ptrFun = vidI2C0Handler;
	I2C0_vidInit(&i2cConfig);
	
	

	/*Enable maskable interrupts*/
	__enable_irq();
	while(1);
}