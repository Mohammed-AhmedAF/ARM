#ifndef _ADC_INTERFACE_H
#define _ADC_INTERFACE_H

typedef struct 
{
	u8 u8Sequencer;
	u8 u8AnalogInput;
	u8 u8InterrupEnabled;
	u8 u8EventTrigger;
} ADC_Config_t;


void ADC0_vidInit(ADC_Config_t * ADC_Config);
void ADC1_vidInit(ADC_Config_t * ADC_Config);
void ADC_vidStartSampling(void);

/*Macros*/

/*Sequencer*/
#define ADC_SEQUENCER_0 0
#define ADC_SEQUENCER_1 1
#define ADC_SEQUENCER_2 2
#define ADC_SEQUENCER_3 3

/*Event Triggers*/
#define ADC_EVENT_TRIGGER_PROCESSOR 0
#define ADC_EVENT_TRIGGER_CONTINUOUS 1
#define ADC_EVENT_TRIGGER_EXTERNAL 4

/*Interrupt*/
#define ADC_INTERRUPT_DISABLED 0
#define ADC_INTERRUPT_ENABLED 1

/*Analog input*/
#define ADC_ANALOGINPUT_0 0
#define ADC_ANALOGINPUT_1 1
#define ADC_ANALOGINPUT_2 2
#define ADC_ANALOGINPUT_3 3
#define ADC_ANALOGINPUT_4 4
#define ADC_ANALOGINPUT_5 5
#define ADC_ANALOGINPUT_6 6
#define ADC_ANALOGINPUT_7 7
#define ADC_ANALOGINPUT_8 8
#define ADC_ANALOGINPUT_9 9
#define ADC_ANALOGINPUT_10 10
#define ADC_ANALOGINPUT_11 11

#endif
