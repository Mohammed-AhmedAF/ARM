#include "Macros.h"
#include "STD_TYPES.h"
#include <FreeRTOS.h>
#include <task.h>
#include <event_groups.h>
#include "SYSCNTRL_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"
#include "UART_interface.h"

void vidToggleLEDs(void * ptrParam);
void vidProcessButtons(void);
void vidControlWatch(void * prtParam);


#define RED_EVENT_BIT 0x01
#define BLUE_EVENT_BIT 0x10
#define UPDATE_DISPLAY 0x02

static EventGroupHandle_t myEventGroup;
TaskHandle_t redTaskHandle;

/*Time variables*/
u8 u8Seconds = 0;
u8 u8Minutes = 0;
u8 u8Hourse = 0;

void vidToggleLEDs(void * ptrParam)
{
	EventBits_t receivedEvents;
	while(1)
	{
		receivedEvents = xEventGroupWaitBits(myEventGroup,RED_EVENT_BIT|BLUE_EVENT_BIT|UPDATE_DISPLAY,pdTRUE,pdFALSE,portMAX_DELAY);
		if (receivedEvents == RED_EVENT_BIT)
		{
			GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
		}
		else if (receivedEvents == BLUE_EVENT_BIT)
		{
			GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN2);
		}
		else if (receivedEvents == UPDATE_DISPLAY)
		{
			UART_vidSendNumber(UART0_vidSendByte,u8Hourse);
			UART0_vidSendByte(':');
			UART_vidSendNumber(UART0_vidSendByte,u8Minutes);
			UART0_vidSendByte(':');
			UART_vidSendNumber(UART0_vidSendByte,u8Seconds);
			UART0_vidSendByte('\n');
			UART0_vidSendByte('\r');
		}
	}
}

void vidControlWatch(void * ptrParam)
{
	TickType_t xLastWakeTime = xTaskGetTickCount();
	const TickType_t xDelay = pdMS_TO_TICKS(1000);
	while(1)
	{
		u8Seconds++;
		xEventGroupSetBits(myEventGroup,UPDATE_DISPLAY);
		vTaskDelayUntil(&xLastWakeTime,xDelay);

	}
}


void vidProcessButtons(void)
{
	BaseType_t xHigherPriorityTaskWoken, xResult;
	xHigherPriorityTaskWoken = pdFALSE;
	
	if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN0))
	{
		xEventGroupSetBitsFromISR(myEventGroup,RED_EVENT_BIT,&xHigherPriorityTaskWoken);
		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken)
		GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN0);
	}
	else if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN4)) 
	{
		xEventGroupSetBitsFromISR(myEventGroup,BLUE_EVENT_BIT,&xHigherPriorityTaskWoken);
		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken)
		GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN4);

	}
}

int main(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);

	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);
	
	/*Pin unlocking (required)*/
	GPIO_vidUnlock(GPIO_PORTF);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN0);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN4);
	GPIO_vidLock(GPIO_PORTF);
	
	GPIOConfig_t gpioButton0Conf;
	gpioButton0Conf.u8AlternateFunc = GPIO_ALTERFUNC_UNSET;
	gpioButton0Conf.u8DigEnable = GPIO_DEN_SET;
	gpioButton0Conf.u8Direction = GPIO_DIR_INPUT;
	gpioButton0Conf.u8Port = GPIO_PORTF;
	gpioButton0Conf.u8Pin = GPIO_PIN0;
	GPIO_vidConfigurePin(&gpioButton0Conf);
	
	gpioButton0Conf.u8Pin = GPIO_PIN4;
	GPIO_vidConfigurePin(&gpioButton0Conf);
	
	ExtInterruptConfig_t Ext0Conf;
	Ext0Conf.ptrFunc = vidProcessButtons;
	Ext0Conf.u8BothEdges = GPIO_INTERRUPT_EVENTCONTROLLED;
	Ext0Conf.u8InterruptEvent = GPIO_EVENT_FALLINGEDGE;
	Ext0Conf.u8InterruptSense = GPIO_SENSE_EDGE;
	Ext0Conf.u8PullResistance = GPIO_PUR_ENABLED;
	
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN0,&Ext0Conf);
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN4,&Ext0Conf);
	
	NVIC_vidSetInterrupt(NVIC_GPIOF);
	NVIC_vidSetPriority(NVIC_GPIOF,6);
	
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x01);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN1,0x01);

	
	UARTConfig_t UART0Config;
	UART0Config.u8InterruptEnabled = UART_INTERRUPT_DISABLED;
	UART0Config.u8FIFOEnabled = UART_FIFO_ENABLED;
	UART0Config.u8HighSpeedEnabled = UART_HIGHSPEED_DIV16;
	UART0Config.u8RxTx  = UART_RXTX_BOTH;
	UART0Config.u8WordLength = UART_WORDSIZE_8;
	UART0Config.u8ClockSource = UART_CLOCKSOURCE_RC;
	UART0Config.u16Integer = 8;
	UART0Config.u8Fraction = 44;
	UART0_vidInit(&UART0Config);
	
	
	/*Event group*/
	myEventGroup = xEventGroupCreate();
	
	/*Creating RTOS tasks*/
	xTaskCreate(vidToggleLEDs,"Toggling",100,NULL,2,&redTaskHandle);
	xTaskCreate(vidControlWatch,"Control",100,NULL,1,NULL);
	
	vTaskStartScheduler();
	
	__enable_irq();
	
	while(1);
}