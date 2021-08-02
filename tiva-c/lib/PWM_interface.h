#ifndef _PWM_INTERFACE_H
#define _PWM_INTERFACE_H

typedef struct {
	u8 u8Module;
	u8 u8Generator;
	u8 u8Channel;
	u8 u8CountDirection;
	u16 u16LoadVal;
	u16 u16CompVal;
}PWMConfig_t;

void PWM_vidInit(PWMConfig_t * ptPWMConfig);
static void PWM_vidConfigCountDir(u8 u8Module, u8 u8Generator, u8 u8CountDir);
static void PWM_vidEnableGenerator(u8 u8Module, u8 u8Generator);
static void PWM_vidDisableGenerator(u8 u8Module, u8 u8Generator);
static void PWM_vidSelectChannel(u8 u8Module, u8 u8Channel);
static void PWM_vidAssignLoadVal(u8 u8Module, u8 u8Generator, u16 u16LoadVal);
static void PWM_vidAssignCompVal(u8 u8Module, u8 u8Generator, u16 u16CompVal);



#define PWM_MODULE_0 0
#define PWM_MODULE_1 1
#define PWM_COUNTDIR_UP 1
#define PWM_COUNTDIR_DOWN 0

#define PWM_CHANNEL_0 0
#define PWM_CHANNEL_1 1
#define PWM_CHANNEL_2 2
#define PWM_CHANNEL_3 3

#define PWM_GENERTOR_0 0
#define PWM_GENERATOR_1 1
#define PWM_GENERATOR_2 2
#define PWM_GENERATOR_3 3

#endif