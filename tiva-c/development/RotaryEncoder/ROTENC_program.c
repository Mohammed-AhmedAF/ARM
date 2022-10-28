#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "ROTENC_interface.h"
#include "UART_interface.h"
#include "TIMER0_interface.h"

static u8 u8LastClkState;
static u8 u8CurrentClkState;
static u8 u8Counter;
static ROTENCRead_t strctROTENCRead;

void ROTENC_vidInit(ROTENCConfig_t const * config)
{
	/*CLK pin*/
	GPIO_vidSetPinDigEnable(config->u8ClockPort,config->u8ClockPin,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(config->u8ClockPort,config->u8ClockPin,GPIO_DIR_INPUT);
	GPIO_vidConfigurePUR(config->u8ClockPort,config->u8ClockPin,GPIO_PUR_ENABLED);
	
	/*DT pin*/
	GPIO_vidSetPinDigEnable(config->u8DataPort,config->u8DataPin,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(config->u8DataPort,config->u8DataPin,GPIO_DIR_INPUT);
	GPIO_vidConfigurePUR(config->u8DataPort,config->u8DataPin,GPIO_PUR_ENABLED);
	
	/*Populate the LastClkState*/
	u8LastClkState = GPIO_u8GetPinValue(config->u8ClockPort,config->u8ClockPin);
}

ROTENCRead_t ROTENC_strctGetReading(ROTENCConfig_t const * config)
{
	u8CurrentClkState = GPIO_u8GetPinValue(config->u8ClockPort,config->u8ClockPin);
	
	if (u8CurrentClkState != u8LastClkState)
	{
		u8 u8DataState = GPIO_u8GetPinValue(config->u8DataPort,config->u8DataPin);
		if (u8DataState != u8CurrentClkState)
		{
			u8Counter--;
			strctROTENCRead.u8Direction = ROTENC_DIR_CCW;
			UART0_vidSendString("Counter-clockwise\r\n");
		}
		else
		{
			u8Counter++;
			strctROTENCRead.u8Direction = ROTENC_DIR_CW;
			UART0_vidSendString("Clockwise\r\n");
		}

	}
	u8LastClkState = u8CurrentClkState;
	TIMER0_vidDelayMilli(100);
	return strctROTENCRead;
}
