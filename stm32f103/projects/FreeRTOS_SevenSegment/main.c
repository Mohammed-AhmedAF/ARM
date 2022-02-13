#include "Macros.h"
#include "STD_TYPES.h"
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "SevenSegment_interface.h"

void Task0(void * ptr);
void Task1(void * ptr);

void Task0(void * prt)
{
  TickType_t delayTime = pdMS_TO_TICKS(500);
	u8 u8Digital = 0;
	
	while(1)
	{
		SevenSegment_vidWriteMultiDigit(u8Digital);
		u8Digital++;
		vTaskDelay(delayTime);
		if (u8Digital == 60)
		{
			u8Digital =0;
		}
	}
}

int main(void)
{
	RCC_voidEnableClock(RCC_APB2,RCC_GPIO_PORTA);
	RCC_voidEnableClock(RCC_APB2,RCC_GPIO_PORTB);
	
	GPIO_vidSetPinMode(GPIO_PORTA,GPIO_PIN0,GPIO_OUTSPEED_10);
	GPIO_vidSetPinConfiguration(GPIO_PORTA,GPIO_PIN0,GPIO_GPOUT_PP);

	GPIO_vidSetPinMode(GPIO_PORTA,GPIO_PIN1,GPIO_OUTSPEED_10);
	GPIO_vidSetPinConfiguration(GPIO_PORTA,GPIO_PIN1,GPIO_GPOUT_PP);
	SevenSegment_vidInit();

	xTaskCreate(Task0,"Blink",100,NULL,1,NULL);

	
	vTaskStartScheduler();
	
	while(1);
}