#include "Macros.h"
#include "STD_TYPES.h"
#include "ADC_private.h"
#include "ADC_interface.h"
#include "TM4C123.h"                    // Device header

volatile u32 u32ADCResult;

void ADC0_vidInit(ADC_Config_t * ADC_Config)
{
	/*Ensure disabling of sample sequencer*/
	CLEAR_BIT(ADC0->ACTSS,3);
	/*Proccessor Sample Sequence Initiate*/
	
	/*Event trigger*/
	/**/
	switch(ADC_Config->u8EventTrigger)
	{
		case ADC_EVENT_TRIGGER_PROCESSOR:
		ADC0->EMUX = ~0x0<12;
		break;
		case ADC_EVENT_TRIGGER_CONTINUOUS:
		ADC0->EMUX = ~0xF<12;
		break;
	}
	/*Selecting analog input*/
	/*Analog input 2: PE1*/
	ADC0->SSMUX3 = ADC_Config->u8AnalogInput;
	
	ADC0->SSCTL3 |= 0x6;
	
	/*Enabling interrupt*/
	if (ADC_Config->u8InterrupEnabled)
	{
			SET_BIT(ADC0->IM,3);
	}
	else
	{
			CLEAR_BIT(ADC0->IM,3);

	}
	/*Enabling sample sequencer 3*/
	SET_BIT(ADC0->ACTSS,3);

	SET_BIT(ADC0->PSSI,3);
}

void ADC1_vidInit(ADC_Config_t * ADC_Config)
{
	/*Ensure disabling of sample sequencer*/
	switch(ADC_Config->u8Sequencer)
	{
		case ADC_SEQUENCER_0:
		CLEAR_BIT(ADC1->ACTSS,0);
		break;
		case ADC_SEQUENCER_1:
			CLEAR_BIT(ADC1->ACTSS,1);
		break;
		case ADC_SEQUENCER_2:
			CLEAR_BIT(ADC1->ACTSS,2);
		break;
		case ADC_SEQUENCER_3:
		CLEAR_BIT(ADC1->ACTSS,3);
		break;
	}
		/*Proccessor Sample Sequence Initiate*/
	
	/*Event trigger*/
	/*Processor*/
		switch(ADC_Config->u8EventTrigger)
	{
		case ADC_EVENT_TRIGGER_PROCESSOR:
		ADC1->EMUX = ~0x0<12;
		break;
		case ADC_EVENT_TRIGGER_CONTINUOUS:
		ADC1->EMUX = ~0xF<12;
		break;
	}

	/*Selecting analog input*/
	/*Analog input 2: PE1*/
	switch(ADC_Config->u8Sequencer)
	{
		case ADC_SEQUENCER_0:
		ADC1->SSMUX0 = ADC_Config->u8AnalogInput;
		break;
		case ADC_SEQUENCER_1:
		ADC1->SSMUX1 = ADC_Config->u8AnalogInput;
		break;
		case ADC_SEQUENCER_2:
		ADC1->SSMUX2 = ADC_Config->u8AnalogInput;
		break;
		case ADC_SEQUENCER_3:
		ADC1->SSMUX3 = ADC_Config->u8AnalogInput;
		break;
	}
	ADC1->SSCTL3 |= 0x6;
	
	/*Enabling interrupt*/
	SET_BIT(ADC1->IM,3);
	
	/*Enabling sample sequencer 3*/
		switch(ADC_Config->u8Sequencer)
	{
		case ADC_SEQUENCER_0:
				SET_BIT(ADC1->ACTSS,0);
		break;
		case ADC_SEQUENCER_1:
				SET_BIT(ADC1->ACTSS,1);
		break;
		case ADC_SEQUENCER_2:
				SET_BIT(ADC1->ACTSS,2);
		break;
		case ADC_SEQUENCER_3:
				SET_BIT(ADC1->ACTSS,3);
		break;
	}

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
