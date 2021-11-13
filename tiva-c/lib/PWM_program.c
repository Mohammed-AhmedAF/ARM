#include "STD_TYPES.h"
#include "Macros.h"
#include "PWM_private.h"
#include "PWM_interface.h"
#include "TM4C123.h"                    // Device header

/********/
/*Status: Not fully tested*/
/********/

static void (*ptFPWM_0_callback) (void);
static void (*ptFPWM_1_callback) (void);
static void (*ptFPWM_2_callback) (void);
static void (*ptFPWM_3_callback) (void);

void PWM_vidInit(PWMConfig_t * ptPWMConfig)
{
		/*Disabling generator*/
		PWM_vidDisableGenerator(ptPWMConfig->u8Module,ptPWMConfig->u8Generator);

		/*Count direction*/
		PWM_vidConfigCountDir(ptPWMConfig->u8Module,ptPWMConfig->u8Generator,ptPWMConfig->u8CountDirection);
		
		/*Action*/
		PWM_vidSetOutput(ptPWMConfig->u8Module,ptPWMConfig->u8Generator,ptPWMConfig->u8Output);
	
		/*Load value*/
		PWM_vidAssignLoadVal(ptPWMConfig->u8Module,ptPWMConfig->u8Generator,ptPWMConfig->u16LoadVal);
	
		/*Compare value*/
		PWM_vidAssignCompVal(ptPWMConfig->u8Module,ptPWMConfig->u8Generator,ptPWMConfig->u16CompVal);

		/*Enable generator*/
		PWM_vidEnableGenerator(ptPWMConfig->u8Module,ptPWMConfig->u8Generator);

		/*Selecting channel*/
		PWM_vidSelectChannel(ptPWMConfig->u8Module,ptPWMConfig->u8Channel);
	
}

void PWM_vidConfigCountDir(u8 u8Module, u8 u8Generator, u8 u8CountDir)
{
	if (u8Module == PWM_MODULE_0)
	{
		if (u8CountDir == PWM_COUNTDIR_DOWN)
		{
			switch(u8Generator)
			{
				case PWM_GENERATOR_0:
					CLEAR_BIT(PWM0_CTL0,1);
					break;
				case PWM_GENERATOR_1:
					CLEAR_BIT(PWM0_CTL1,1);
					break;
				case PWM_GENERATOR_2:
					CLEAR_BIT(PWM0_CTL2,1);
					break;
				case PWM_GENERATOR_3:
					CLEAR_BIT(PWM0_CTL3,1);
					break;
			}
		}
		else
		{
			switch(u8Generator)
			{
				case PWM_GENERATOR_0:
					SET_BIT(PWM0_CTL0,1);
					break;
				case PWM_GENERATOR_1:
					SET_BIT(PWM0_CTL1,1);
					break;
				case PWM_GENERATOR_2:
					SET_BIT(PWM0_CTL2,1);
					break;
				case PWM_GENERATOR_3:
					SET_BIT(PWM0_CTL3,1);
					break;
			}
		}
	}
	else
	{
	}
}

void PWM_vidEnableGenerator(u8 u8Module, u8 u8Generator)
{
	if (u8Module == PWM_MODULE_0)
	{
		switch(u8Generator)
		{
			case PWM_GENERATOR_0:
					SET_BIT(PWM0_CTL0,0);
					break;
				case PWM_GENERATOR_1:
					SET_BIT(PWM0_CTL1,0);
					break;
				case PWM_GENERATOR_2:
					SET_BIT(PWM0_CTL2,0);
					break;
				case PWM_GENERATOR_3:
					SET_BIT(PWM0_CTL3,0);
					break;
		}
	}
	else
	{
	
	}
}

void PWM_vidDisableGenerator(u8 u8Module, u8 u8Generator)
{
	if (u8Module == PWM_MODULE_0)
	{
		switch(u8Generator)
		{
			case PWM_GENERATOR_0:
					CLEAR_BIT(PWM0_CTL0,0);
					break;
				case PWM_GENERATOR_1:
					CLEAR_BIT(PWM0_CTL1,0);
					break;
				case PWM_GENERATOR_2:
					CLEAR_BIT(PWM0_CTL2,0);
					break;
				case PWM_GENERATOR_3:
					CLEAR_BIT(PWM0_CTL3,0);
					break;
		}
	}
	else
	{
	
	}
}

void PWM_vidSelectChannel(u8 u8Module,u8 u8Channel)
{
	if (u8Module == PWM_MODULE_0)
	{
		PWM0_ENABLE |= (1<<u8Channel);
	}
	else if (u8Module == PWM_MODULE_1)
	{
		//PWM1_ENABLE |= (1<<u8Channel);
	}
}	

void PWM_vidAssignLoadVal(u8 u8Module, u8 u8Generator, u16 u16LoadVal)
{
	if (u8Module == PWM_MODULE_0)
	{
		switch(u8Generator)
		{
			case PWM_GENERATOR_0:
					PWM0_LOAD0 = u16LoadVal;
					break;
				case PWM_GENERATOR_1:
					PWM0_LOAD1 = u16LoadVal;
					break;
				case PWM_GENERATOR_2:
					PWM0_LOAD2 = u16LoadVal;
					break;
				case PWM_GENERATOR_3:
					PWM0_LOAD3 = u16LoadVal;
					break;
		}
	}
	else
	{
	
	}
}

void PWM_vidAssignCompVal(u8 u8Module, u8 u8Generator, u16 u16CompVal)
{
	if (u8Module == PWM_MODULE_0)
	{
		switch(u8Generator)
		{
			case PWM_GENERATOR_0:
					PWM0_CMPA0 = u16CompVal;
					break;
				case PWM_GENERATOR_1:
					PWM0_CMPA1 = u16CompVal;
					break;
				case PWM_GENERATOR_2:
					PWM0_CMPA2 = u16CompVal;
					break;
				case PWM_GENERATOR_3:
					PWM0_CMPA3 = u16CompVal;
					break;
		}
	}
	else
	{
		switch(u8Generator)
		{
				case PWM_GENERATOR_0:
					PWM0_CMPB0 = u16CompVal;
					break;
				case PWM_GENERATOR_1:
					PWM0_CMPB1 = u16CompVal;
					break;
				case PWM_GENERATOR_2:
					PWM0_CMPB2 = u16CompVal;
					break;
				case PWM_GENERATOR_3:
					PWM0_CMPB3 = u16CompVal;
					break;
		}
	}
}

void PWM_vidSetCompValue(u8 u8Module,u8 u8Generator, u8 u8Channel, u16 u16CompVal)
{
	if (u8Module == PWM_MODULE_0)
	{
		switch(u8Generator)
		{
			case PWM_GENERATOR_0:
					if (u8Channel == PWM_CHANNEL_0)
					{
					PWM0_CMPA0 = u16CompVal;
					}
					else if (u8Channel == PWM_CHANNEL_1)
					{
					PWM0_CMPB0 = u16CompVal;
					}
					break;
				case PWM_GENERATOR_1:
					if (u8Channel == PWM_CHANNEL_0)
					{
					PWM0_CMPA1 = u16CompVal;
					}
					else
					{
					PWM0_CMPB1 = u16CompVal;
					}
					break;
				case PWM_GENERATOR_2:
					PWM0_CMPA2 = u16CompVal;
					break;
				case PWM_GENERATOR_3:
					PWM0_CMPA3 = u16CompVal;
					break;
		}
	}
}

void PWM_vidSetOutput(u8 u8Module, u8 u8Generator, u8 u8Output)
{
		if (u8Module == PWM_MODULE_0)
	{
		switch(u8Generator)
		{
			case PWM_GENERATOR_0:
					PWM0_GENA0 = u8Output;
					break;
				case PWM_GENERATOR_1:
					PWM0_GENA1 = u8Output;
					break;
				case PWM_GENERATOR_2:
					PWM0_GENA2 = u8Output;
					break;
				case PWM_GENERATOR_3:
					PWM0_GENA3 = u8Output;
					break;
		}
	}
	else
	{
	switch(u8Generator)
		{
			case PWM_GENERATOR_0:
					PWM0_GENB0 = u8Output;
					break;
				case PWM_GENERATOR_1:
					PWM0_GENB1 = u8Output;
					break;
				case PWM_GENERATOR_2:
					PWM0_GENB2 = u8Output;
					break;
				case PWM_GENERATOR_3:
					PWM0_GENB3 = u8Output;
					break;
		}
	}
}

void PWM_vidSetOutput_test(u8 u8Module, u8 u8Generator,u8 u8Block, u8 u8Output)
{
	if (u8Module == PWM_MODULE_0)
	{
		switch(u8Generator)
		{
			case PWM_GENERATOR_0:
				if (u8Block == PWM_BLOCK_A)
				{
					PWM0_GENA0 = u8Output;
				}
				else
				{
					PWM0_GENB0 = u8Output;
				}
					break;
				case PWM_GENERATOR_1:
					PWM0_GENA1 = u8Output;
					break;
				case PWM_GENERATOR_2:
					PWM0_GENA2 = u8Output;
					break;
				case PWM_GENERATOR_3:
					PWM0_GENA3 = u8Output;
					break;
		}
	}
}

void PWM_vidEnableInterrupt(u8 u8Module, u8 u8Generator,u8 u8InterruptID)
{
	if (u8Module == PWM_MODULE_0)
	{
		PWM0_INTEN |= (1<<u8Generator);
		switch(u8Generator)
		{
			case PWM_GENERATOR_0:
					PWM0_INTEN0 = u8InterruptID;
				break;
			case PWM_GENERATOR_1:
					PWM0_INTEN1 = u8InterruptID;
				break;
			case PWM_GENERATOR_2:
					PWM0_INTEN2 = u8InterruptID;
				break;
			case PWM_GENERATOR_3:
					PWM0_INTEN3 = u8InterruptID;
				break;
		}
	}
	else
	{
	
	
	}
}

void PWM_vidPutISRFunction(u8 u8Generator,void (*ptrF) (void))
{
	switch(u8Generator)
	{
		case PWM_GENERATOR_0:
		ptFPWM_0_callback = ptrF;
		break;
		case PWM_GENERATOR_1:
		ptFPWM_1_callback = ptrF;
		break;
		case PWM_GENERATOR_2:
		ptFPWM_2_callback = ptrF;
		break;
		case PWM_GENERATOR_3:
		ptFPWM_3_callback = ptrF;
		break;
	}
}

void PWM0_0_Handler(void)
{
	ptFPWM_0_callback();
}

void PWM0_1_Handler(void)
{
	ptFPWM_1_callback();
}

void PWM0_2_Handler(void)
{
	ptFPWM_2_callback();
}

void PWM0_3_Handler(void)
{
	ptFPWM_3_callback();
}

