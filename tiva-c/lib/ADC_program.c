#include "Macros.h"
#include "STD_TYPES.h"
#include "ADC_private.h"
#include "ADC_interface.h"
#include "TM4C123.h"                    // Device header

volatile u32 u32ADCResult;

void ADC0_vidInit(void)
{
	/*Ensure disabling of sample sequencer*/
	CLEAR_BIT(ADC0->ACTSS,3);
	/*Proccessor Sample Sequence Initiate*/
	
	/*Event trigger*/
	/*Processor*/
	ADC0->EMUX = ~0xF<12;

	/*Selecting analog input*/
	/*Analog input 2: PE1*/
	ADC0->SSMUX3 = 2;
	
	ADC0->SSCTL3 |= 0x6;
	
	/*Enabling interrupt*/
	SET_BIT(ADC0->IM,3);
	
	/*Enabling sample sequencer 3*/
	SET_BIT(ADC0->ACTSS,3);

	SET_BIT(ADC0->PSSI,3);
}

void ADC1_vidInit(void)
{
	/*Ensure disabling of sample sequencer*/
	CLEAR_BIT(ADC1->ACTSS,3);
	/*Proccessor Sample Sequence Initiate*/
	
	/*Event trigger*/
	/*Processor*/
	ADC1->EMUX = ~0xF<12;

	/*Selecting analog input*/
	/*Analog input 2: PE1*/
	ADC1->SSMUX3 = 2;
	
	ADC1->SSCTL3 |= 0x6;
	
	/*Enabling interrupt*/
	SET_BIT(ADC1->IM,3);
	
	/*Enabling sample sequencer 3*/
	SET_BIT(ADC1->ACTSS,3);

	SET_BIT(ADC1->PSSI,3);
}

void ADC_vidStartSampling(void)
{
	SET_BIT(ADC1->PSSI,3);
}

void ADC0SS3_Handler()
{
	u32ADCResult = ADC0->SSFIFO3;
	ADC0->ISC |= (1<<3);
	ADC0->PSSI |= (1<<3);
}

void ADC1SS3_Handler()
{
	u32ADCResult = ADC1->SSFIFO3;
	ADC1->ISC |= (1<<3);
	ADC1->PSSI |= (1<<3);
}
