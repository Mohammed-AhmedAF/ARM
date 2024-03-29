#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "HBRIDGE_config.h"
#include "HBRIDGE_interface.h"

void HBRIDGE_vidInit(void)
{
	/*Right*/
	GPIO_vidSetPinDirection(HBRIDGE_R0_PORT,HBRIDGE_R0_PIN,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(HBRIDGE_R0_PORT,HBRIDGE_R0_PIN,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(HBRIDGE_R1_PORT,HBRIDGE_R1_PIN,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(HBRIDGE_R1_PORT,HBRIDGE_R1_PIN,GPIO_DEN_SET);
	
	/*Left*/
	GPIO_vidSetPinDirection(HBRIDGE_L0_PORT,HBRIDGE_L0_PIN,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(HBRIDGE_L0_PORT,HBRIDGE_L0_PIN,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(HBRIDGE_L1_PORT,HBRIDGE_L1_PIN,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(HBRIDGE_L1_PORT,HBRIDGE_L1_PIN,GPIO_DEN_SET);
}

void HBRIDGE_vidControl(u8 u8Command)
{
  switch(u8Command)
	{
		case HBRIDGE_COMMAND_BOTH_FORWARD:
			/*Right*/
			GPIO_vidSetPinValue(HBRIDGE_R0_PORT,HBRIDGE_R0_PIN,STD_HIGH);
			GPIO_vidSetPinValue(HBRIDGE_R1_PORT,HBRIDGE_R1_PIN,STD_LOW);
			/*Left*/
			GPIO_vidSetPinValue(HBRIDGE_L0_PORT,HBRIDGE_L0_PIN,STD_LOW);
			GPIO_vidSetPinValue(HBRIDGE_L0_PORT,HBRIDGE_L0_PIN,STD_HIGH);
			break;
		case HBRIDGE_COMMAND_BOTH_BACKWARD:
			/*Right*/
			GPIO_vidSetPinValue(HBRIDGE_R0_PORT,HBRIDGE_R0_PIN,STD_LOW);
			GPIO_vidSetPinValue(HBRIDGE_R1_PORT,HBRIDGE_R1_PIN,STD_HIGH);
			/*Left*/
			GPIO_vidSetPinValue(HBRIDGE_L0_PORT,HBRIDGE_L0_PIN,STD_HIGH);
			GPIO_vidSetPinValue(HBRIDGE_L0_PORT,HBRIDGE_L0_PIN,STD_LOW);
			break;
		case HBRIDGE_COMMAND_BOTH_STOP:
			/*Right*/
			GPIO_vidSetPinValue(HBRIDGE_R0_PORT,HBRIDGE_R0_PIN,STD_LOW);
			GPIO_vidSetPinValue(HBRIDGE_R1_PORT,HBRIDGE_R1_PIN,STD_LOW);
			/*Left*/
			GPIO_vidSetPinValue(HBRIDGE_L0_PORT,HBRIDGE_L0_PIN,STD_LOW);
			GPIO_vidSetPinValue(HBRIDGE_L0_PORT,HBRIDGE_L0_PIN,STD_LOW);
			break;
		case HBRIDGE_COMMAND_RIGHT_FORWARD:
			/*Right*/
			GPIO_vidSetPinValue(HBRIDGE_R0_PORT,HBRIDGE_R0_PIN,STD_HIGH);
			GPIO_vidSetPinValue(HBRIDGE_R1_PORT,HBRIDGE_R1_PIN,STD_LOW);
			/*Left*/
			GPIO_vidSetPinValue(HBRIDGE_L0_PORT,HBRIDGE_L0_PIN,STD_LOW);
			GPIO_vidSetPinValue(HBRIDGE_L0_PORT,HBRIDGE_L0_PIN,STD_LOW);
			break;
		case HBRIDGE_COMMAND_RIGHT_BACKWARD:
			/*Right*/
			GPIO_vidSetPinValue(HBRIDGE_R0_PORT,HBRIDGE_R0_PIN,STD_LOW);
			GPIO_vidSetPinValue(HBRIDGE_R1_PORT,HBRIDGE_R1_PIN,STD_HIGH);
			/*Left*/
			GPIO_vidSetPinValue(HBRIDGE_L0_PORT,HBRIDGE_L0_PIN,STD_LOW);
			GPIO_vidSetPinValue(HBRIDGE_L0_PORT,HBRIDGE_L0_PIN,STD_LOW);
			break;
		case HBRIDGE_COMMAND_LEFT_FORWARD:
			/*Right*/
			GPIO_vidSetPinValue(HBRIDGE_R0_PORT,HBRIDGE_R0_PIN,STD_LOW);
			GPIO_vidSetPinValue(HBRIDGE_R1_PORT,HBRIDGE_R1_PIN,STD_LOW);
			/*Left*/
			GPIO_vidSetPinValue(HBRIDGE_L0_PORT,HBRIDGE_L0_PIN,STD_LOW);
			GPIO_vidSetPinValue(HBRIDGE_L0_PORT,HBRIDGE_L0_PIN,STD_HIGH);
			break;
		case HBRIDGE_COMMAND_LEFT_BACKWARD:
			/*Right*/
			GPIO_vidSetPinValue(HBRIDGE_R0_PORT,HBRIDGE_R0_PIN,STD_LOW);
			GPIO_vidSetPinValue(HBRIDGE_R1_PORT,HBRIDGE_R1_PIN,STD_LOW);
			/*Left*/
			GPIO_vidSetPinValue(HBRIDGE_L0_PORT,HBRIDGE_L0_PIN,STD_HIGH);
			GPIO_vidSetPinValue(HBRIDGE_L0_PORT,HBRIDGE_L0_PIN,STD_LOW);
			break;
	}
}