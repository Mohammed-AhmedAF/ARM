#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "SPI_private.h"
#include "SPI_interface.h"
#include "SYSCNTRL_interface.h"

void Delay_ms(int);

/*D0: Clk*/
/*D1: SS*/
/*D2: Rx*/
/*D3: Tx*/

int main(void)
{
	
	SYSCNTRL_vidEnableSPIClock(SYSCNTRL_SPI1);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTD);
	
	/*Configuring LED pins*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN2,STD_HIGH);
	
	 GPIOD_AMSEL &= ~0x09;      /* disable analog functionality RD0 and RD3 */
	
	/*Configuring SPI pins*/
	GPIO_vidSetPinDigEnable(GPIO_PORTD,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTD,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTD,GPIO_PIN2,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTD,GPIO_PIN3,GPIO_DEN_SET);
	
	/*Slave select*/
	GPIO_vidSetPinDirection(GPIO_PORTD,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTD,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidSetPinValue(GPIO_PORTD,GPIO_PIN1,STD_HIGH);
	
	/*Enable alternate function*/
	GPIO_vidSelectAlterFunction(GPIO_PORTD,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTD,GPIO_PIN3);

	
	
	  GPIOD_PCTL &= ~0x0000F00F; /* assign RD0 and RD3 pins to SPI1 */
    GPIOD_PCTL |= 0x00002002;
		
		u8 val1 = 'A';
	  u8 val2 = 'B';

    SPI_vidInit();
    while(1)
		{              
    SPI_vidSendByte(val1); /* write a character */
    Delay_ms(1000);
		SPI_vidSendByte(val2); /* write a character */
    Delay_ms(1000);	
    }

}

void Delay_ms(int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  /* excute NOP for 1ms */
}