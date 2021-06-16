#ifndef _ADC_INTERFACE_H
#define _ADC_INTERFACE_H

typedef struct 
{
	u8 u8Sequencer;
} ADC_Config_t;


void ADC0_vidInit(void);
void ADC1_vidInit(void);
void ADC_vidStartSampling(void);

/*Macros*/
#define ADC_EVENT_TRIGGER_PROCESSOR 0
#define ADC_EVENT_TRIGGER_CONTINUOUS 1

#endif
