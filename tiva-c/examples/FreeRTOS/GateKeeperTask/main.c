#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "Macros.h"
#include "STD_TYPES.h"
#include "SYSCNTRL_interface.h"
#include "GPIO_interface.h"
#include "UART_interface.h"

void sender1Task (void * ptr);
void sender2Task (void * ptr);
void gateKeeperTask (void * ptr);

QueueHandle_t queueMessage;
static const u8 * messagesArr[] = 
{
"Task 1 ############################## Task1 \r\n",
"Task 2 ------------------------------ Task2 \r\n"
};

void sender1Task (void * ptr)
{

	while(1)
	{
		xQueueSend(queueMessage,&messagesArr[0],portMAX_DELAY);
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

void sender2Task (void * ptr)
{
	while(1)
	{
		xQueueSend(queueMessage,&messagesArr[1],portMAX_DELAY);
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

void gateKeeperTask(void * ptr)
{
	u8 * messageToPrint;
	while(1)
	{
		xQueueReceive(queueMessage,&messageToPrint,portMAX_DELAY);
		UART0_vidSendString(messageToPrint);
	}
}

int main(void)
{
	/*Clock for used peripherals*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	
	/*UART pin configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN0,GPIO_OUTPUT);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x1);
	
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN1,0x1);
	
	/*UART peripheral configuration*/
	UARTConfig_t uart0Config;
	uart0Config.u8Module = UART_MODULE_0;
	uart0Config.u8RxTx = UART_RXTX_BOTH;
	uart0Config.u8HighSpeedEnabled = UART_HIGHSPEED_DIV16;
	uart0Config.u8FIFOEnabled = UART_FIFO_DISABLED;
	uart0Config.u8InterruptEnabled = UART_INTERRUPT_DISABLED;
	uart0Config.u8ParityEnable = UART_PARITY_DISABLED;
	uart0Config.u8StopBits = UART_STOPBITS_1;
	uart0Config.u8WordLength = UART_WORDSIZE_8;
	uart0Config.u8ClockSource = UART_CLOCKSOURCE_RC;
	uart0Config.u16Integer = 104;
	uart0Config.u8Fraction = 11;
	UART_vidInit(&uart0Config);
	
	/*Creating tasks*/
	xTaskCreate(sender1Task,"Sender1",100,NULL,1,NULL);
	xTaskCreate(sender2Task,"Sender2",100,NULL,2,NULL);
	xTaskCreate(gateKeeperTask,"GateKeeperTask",100,NULL,0,NULL);
	
	queueMessage = xQueueCreate(5,sizeof(u8 *));
	
	/*Start scheduling*/
	vTaskStartScheduler();
	
	while(1);
}
