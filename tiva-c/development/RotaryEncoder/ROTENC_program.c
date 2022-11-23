#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "ROTENC_interface.h"
#include "UART_interface.h"
#include "TIMER0_interface.h"

static u8 u8LastClkState;
static u8 u8CurrentClkState;
volatile u8 u8Counter;
static s8 s8Counter = 0;
static ROTENCRead_t strctROTENCRead;
static (*ptrFuncSwitch) (void);


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
							TIMER0_vidDelayMilli(10);

			strctROTENCRead.u8Direction = ROTENC_DIR_CCW;
			UART0_vidSendString("Counter-clockwise\r\n");

		}
		else
		{
			u8Counter++;
			strctROTENCRead.u8Direction = ROTENC_DIR_CW;
			UART0_vidSendString("Clockwise\r\n");		
			TIMER0_vidDelayMilli(10);

		}

	}
	u8LastClkState = u8CurrentClkState;
								TIMER0_vidDelayMilli(10);

	return strctROTENCRead;
}

/**********************************************/
/*func: ROTENC_strctGetReading_tech()         */
/*param: ROTENCConfig_t *                     */
/*return: void                                *
/*source: *https://controllerstech.com/incremental-encoder-with-stm32//
/*********************************************/
void ROTENC_strctGetReading_tech(ROTENCConfig_t const * config)
{
	if (GPIO_u8GetPinValue(config->u8DataPort,config->u8DataPin) ==STD_LOW )
	{
		/*Counter clockwise*/
	if (GPIO_u8GetPinValue(config->u8ClockPort,config->u8ClockPin) == STD_LOW)
	{
			while(GPIO_u8GetPinValue(config->u8ClockPort,config->u8ClockPin) == STD_LOW){};
			u8Counter--;		
			while(GPIO_u8GetPinValue(config->u8DataPort,config->u8DataPin) == STD_LOW){};
			UART0_vidSendString("CCW\r\n");
	
	}
	else if (GPIO_u8GetPinValue(config->u8ClockPort,config->u8ClockPin) == STD_HIGH)
		{
			while(GPIO_u8GetPinValue(config->u8ClockPort,config->u8ClockPin) == STD_HIGH);
			u8Counter++;
			while(GPIO_u8GetPinValue(config->u8ClockPort,config->u8ClockPin) == STD_LOW);
			UART0_vidSendString("CW\r\n");

		}
	}

}
