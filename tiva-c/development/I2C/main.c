#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "NVIC_interface.h"
#include "I2C_interface.h"
#include "APP_interface.h"

void vidBlink(void);
void vidI2C0Handler(void);
volatile u8 u8Result = 0;
static u8 u8Message[]={'L','C','D','Q','M'};

void vidBlink(void)
{
	u8Result = I2C3_u8SendByte('a');
	if (u8Result == 1)
	{
		//GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_RED);
	}

	if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN0) == STD_HIGH)
	{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);
	GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN0);
	}
	else
	{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_BLUE);
	GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN4);
	}
}

void vidI2C0Handler(void)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);
	I2C3_vidClearInterrupt(I2C_INTERRUPT_RIS_ID);
}

int main(void)
{
	/*Enabling clock for used peripherals*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTD);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidChangeSysClock(SYSCNTRL_SYSCLOCK_16MHZ);
	SYSCNTRL_vidEnableI2CClock(SYSCNTRL_I2C_3);
	
	/*I2C pins GPIO configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTD,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTD,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTD,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTD,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTD,GPIO_PIN0,0x3);
	GPIO_vidConfigPortControl(GPIO_PORTD,GPIO_PIN1,0x3);
	GPIO_vidEnablePinOpenDrain(GPIO_PORTD,GPIO_PIN1);
	
	/*LED GPIO configuration*/
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_GREEN,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_BLUE,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_BLUE,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_RED,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_RED,GPIO_OUTPUT);

	/*Button GPIO configuration*/
	GPIO_vidUnlock(GPIO_PORTF);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN0);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN4);
	GPIO_vidLock(GPIO_PORTF);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_SWITCH2,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_SWITCH2,GPIO_INPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_SWITCH1,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_SWITCH1,GPIO_INPUT);
	
	/*External interrupt configuration*/
	ExtInterruptConfig_t extInterruptConf;
	extInterruptConf.ptrFunc = vidBlink;
	extInterruptConf.u8BothEdges = GPIO_INTERRUPT_EVENTCONTROLLED;
	extInterruptConf.u8InterruptSense = GPIO_SENSE_EDGE;
	extInterruptConf.u8InterruptEvent = GPIO_EVENT_FE;
	extInterruptConf.u8PullResistance = GPIO_PUR_ENABLED;
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN0,&extInterruptConf);
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN4,&extInterruptConf);
	
	/*NVIC external interrupt configuration*/
	NVIC_vidSetInterrupt(NVIC_GPIOF);
	NVIC_vidSetPriority(NVIC_GPIOF,2);
	
	//NVIC_vidSetInterrupt(NVIC_I2C0);
	//NVIC_vidSetPriority(NVIC_I2C0,4);

	/*I2C Configuration*/
	I2CConfig i2cConfig;
	i2cConfig.u8Mode = I2C_MODE_MASTER;
	i2cConfig.u8TimerPeriod = I2C_CALC(16000000,I2C_SPEED_100K);
	i2cConfig.u8Interrupt = I2C_INTERRUPT_RIS_DISABLED;
	i2cConfig.ptrFun = vidI2C0Handler;
	I2C3_vidInit(&i2cConfig);
	
	/*Test functions*/
	SYSTICK_vidInitialize();
	
	/*Enable maskable interrupts*/
	__enable_irq();
	while(1);
}