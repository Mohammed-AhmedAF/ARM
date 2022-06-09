#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "SPI_private.h"
#include "SPI_interface.h"
#include "SYSCNTRL_interface.h"
#include "SysTick_interface.h"
#include "IC74595_interface.h"

void Delay_ms(int);
void vidBlink(void);

/*D0: Clk*/
/*D1: SS*/
/*D2: Rx*/
/*D3: Tx*/
volatile	u8 u8Index = 0;
volatile	u8 u8Val_arr[10] = {0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xFF};
volatile	IC74595Config_t config;


void vidBlink(void)
{


			IC74595_vidTest(&config,u8Val_arr[u8Index]);
			u8Index++;
			if (u8Index == 10)
			{
				u8Index = 0;
			}	
}

int main(void)
{
	/*Enable clock for peripherals*/
	SYSCNTRL_vidEnableSPIClock(SYSCNTRL_SPI1);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTD);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	/*Configuring LED pins*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);
	
	/*Disable angalog function*/
	GPIO_vidConfigAnalogFunction(GPIO_PORTD,GPIO_PIN0,GPIO_ANALOG_CLEAR);
	GPIO_vidConfigAnalogFunction(GPIO_PORTD,GPIO_PIN3,GPIO_ANALOG_CLEAR);

	/*Configuring SPI pins*/
	GPIO_vidSetPinDigEnable(GPIO_PORTD,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTD,GPIO_PIN3,GPIO_DEN_SET);
	
	/*Enable alternate function*/
	GPIO_vidSelectAlterFunction(GPIO_PORTD,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTD,GPIO_PIN3);
	
	/*Port configuration*/	
	GPIO_vidConfigPortControl(GPIO_PORTD,GPIO_PIN0,0x02);
	GPIO_vidConfigPortControl(GPIO_PORTD,GPIO_PIN3,0x02);

	
	/*Slave select*/
	GPIO_vidSetPinDirection(GPIO_PORTD,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTD,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidSetPinValue(GPIO_PORTD,GPIO_PIN1,STD_HIGH);
		
	SysTick_vidInit(SYSTICK_SYSTEM_CLOCK,SYSTICK_INTERRUPT_ENABLED);
	SysTick_vidSetValue(16000000);
	SysTick_vidPutISR(vidBlink);
	SysTick_vidStart();
	u8 val1 = 0x0A;
	u8 val2 = 0x0A;
	config.u8LatchPort = GPIO_PORTA;
	config.u8LatchPin  = GPIO_PIN4;
	config.u8OutEnPort = GPIO_PORTA;
	config.u8OutEnPin = GPIO_PIN3;
	config.u8ClearPort = GPIO_PORTA;
	config.u8ClearPin = GPIO_PIN5;
	
	IC74595_vidInit(&config);
  SPI_vidInit();
  while(1)
	{ 
	
		

   }

}

void Delay_ms(int time_ms)
{
    int i, j;
		int x;
    for(i = 0 ; i < time_ms; i++)
		{
			x = 0;
     for(j = 0; j < 3180; j++)
       {
					x++;
			 }  /* excute NOP for 1ms */
		}
}