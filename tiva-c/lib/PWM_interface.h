#ifndef _PWM_INTERFACE_H
#define _PWM_INTERFACE_H

typedef struct {
	u8 u8Module;
	u8 u8Generator;
	u8 u8Channel;
	u8 u8Output;
	u8 u8CountDirection;
	u16 u16LoadVal;
	u16 u16CompVal;
	
}PWMConfig_t;

void PWM_vidInit(PWMConfig_t * ptPWMConfig);
void PWM_vidConfigCountDir(u8 u8Module, u8 u8Generator, u8 u8CountDir);
void PWM_vidEnableGenerator(u8 u8Module, u8 u8Generator);
void PWM_vidDisableGenerator(u8 u8Module, u8 u8Generator);
void PWM_vidSelectChannel(u8 u8Module, u8 u8Channel);
void PWM_vidAssignLoadVal(u8 u8Module, u8 u8Generator, u16 u16LoadVal);
void PWM_vidAssignCompVal(u8 u8Module, u8 u8Generator, u16 u16CompVal);
void PWM_vidSetOutput(u8 u8Module, u8 u8Generator, u8 u8Output);
void PWM_vidEnableInterrupt(u8 u8Module, u8 u8Generator, u8 u8InterruptID);
void PWM_vidDisableInterrupt(u8 u8Module, u8 u8Generator, u8 u8InterruptID);
void PWM_vidPutISRFunction(u8 u8Generator,void (*ptrF) (void));
void PWM_vidSetCompValue(u8 u8Module,u8 u8Generator, u8 u8Channel, u16 u16CompVal);
void PWM_vidSetOutput_test(u8 u8Module, u8 u8Generator,u8 u8Block, u8 u8Output);


#define PWM_MODULE_0 0
#define PWM_MODULE_1 1
#define PWM_COUNTDIR_UP 1
#define PWM_COUNTDIR_DOWN 0

#define PWM_CHANNEL_0 0
#define PWM_CHANNEL_1 1
#define PWM_CHANNEL_2 2
#define PWM_CHANNEL_3 3

#define PWM_GENERATOR_0 0
#define PWM_GENERATOR_1 1
#define PWM_GENERATOR_2 2
#define PWM_GENERATOR_3 3

#define PWM_BLOCK_A 0
#define PWM_BLOCK_B 1

#define PWM_OUTPUTACT_ZERO_INVERT 0x01
#define PWM_OUTPUTACT_ZERO_LOW 0x02
#define PWM_OUTPUTACT_ZERO_HIGH 0x03
#define PWM_OUTPUTACT_LOAD_INVERT 0x04
#define PWM_OUTPUTACT_LOAD_LOW 0x08
#define PWM_OUTPUTACT_LOAD_HIGH 0x0C
#define PWM_OUTPUTACT_COMPA_UP_INVERT 0x10
#define PWM_OUTPUTACT_COMPA_UP_LOW 0x20
#define PWM_OUTPUTACT_COMPA_UP_HIGH 0x30
#define PWM_OUTPUTACT_COMPA_DOWN_INVERT 0x40
#define PWM_OUTPUTACT_COMPA_DOWN_LOW 0x80
#define PWM_OUTPUTACT_COMPA_DOWN_HIGH 0xC0
#define PWM_OUTPUTACT_COMPB_UP_INVERT 0x10
#define PWM_OUTPUTACT_COMPB_UP_LOW 0x20
#define PWM_OUTPUTACT_COMPB_UP_HIGH 0x30
#define PWM_OUTPUTACT_COMPB_DOWN_INVERT 0x40
#define PWM_OUTPUTACT_COMPB_DOWN_LOW 0x80
#define PWM_OUTPUTACT_COMPB_DOWN_HIGH 0xC0

#define PWM_INTERRUPT_GEN_0 0x01
#define PWM_INTERRUPT_GEN_1 0x02
#define PWM_INTERRUPT_GEN_2 0x04
#define PWM_INTERRUPT_GEN_3 0x08
#define PWM_INTERRUPT_COUNT_ZERO 0x01
#define PWM_INTERRUPT_COUNT_LOAD 0x02
#define PWM_INTERRUPT_COUNT_COMPA_UP 0x04
#define PWM_INTERRUPT_COUNT_COMPA_DOWN 0x08


#endif