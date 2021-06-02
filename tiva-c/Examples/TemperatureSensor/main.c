#include <stdint.h>
#include "Macros.h"
#include "STD_TYPES.h"
#include "inc/tm4c123gh6pm.h"
#include "UART0_interface.h"
#include "GPIO_interface.h"
#include "TM4C123.h"                    // Device header


int main(void)
{
    volatile int temperature;
 
    /* enable clocks */
    SYSCTL_RCGCADC_R |= 1;       /* enable clock to ADC0 */
    SYSCTL_RCGCWTIMER_R |= 1;    /* enable clock to WTimer Block 0 */
		SYSCTL_RCGCGPIO_R |= 1; /*Enable clock for GPIOA*/
		SYSCTL_RCGCUART_R |= 1; /*Enable clock for UART0*/
 
    /* initialize ADC0 */
    ADC0_ACTSS_R &= ~8;          /* disable SS3 during configuration */
    ADC0_EMUX_R &= ~0xF000;
    ADC0_EMUX_R |= 0x5000;       /* timer trigger conversion seq 0 */
    ADC0_SSMUX3_R = 0;           /* get input from channel 0 */
    ADC0_SSCTL3_R |= 0x0E;       /* take chip temperature, set flag at 1st sample */
    ADC0_ACTSS_R |= 8;           /* enable ADC0 sequencer 3 */
 
    /* initialize wtimer 0 to trigger ADC at 1 sample/sec */
    WTIMER0_CTL_R = 0;           /* disable WTimer before initialization */
    WTIMER0_CFG_R = 0x04;        /* 32-bit option */
    WTIMER0_TAMR_R = 0x02;       /* periodic mode and down-counter */
    WTIMER0_TAILR_R = 16000000;  /* WTimer A interval load value reg (1 s) */
    WTIMER0_CTL_R |= 0x20;       /* timer triggers ADC */
    WTIMER0_CTL_R |= 0x01;       /* enable WTimer A after initialization */
 
		/* UART0 initialization */
		UARTConfig_t UARTConfig;
		UARTConfig.u16Integer = 208;
		UARTConfig.u8Fraction = 21;
		UARTConfig.u8ClockSource = UART_CLOCKSOURCE_RC;
		UARTConfig.u8InterruptEnabled = UART_INTERRUPT_ENABLED;
		UARTConfig.u8FIFOEnabled = UART_FIFO_DISABLED;
		UARTConfig.u8RxTx = UART_RXTX_BOTH;
		UARTConfig.u8HighSpeedEnabled = UART_HIGHSPEED_DIV8;
 
		UART0_vidInit(&UARTConfig);
		
			
    /* UART0 TX0 and RX0 use PA0 and PA0. Configure them digital and enable alternate function */
    /* set PE4 and PE5 as digital */
		GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
		GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
		/* Use PE4,PE5 alternate function */
		GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
		GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
    GPIOA->AMSEL = 0;    /* Turn off analog function*/
    GPIOA->PCTL |= 0x11;     /* configure PA0 and PA1 for UART */
 
    while(1) {

        while((ADC0_RIS_R & 8) == 0)
            ;                    /* wait for conversion complete */
        temperature = 147 - (247 * ADC0_SSFIFO3_R) / 4096;
        ADC0_ISC_R = 8;          /* clear completion flag */
				UART0_vidSendNumber(temperature);
				UART0_vidSendString("\r\n");

    }
}