#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
volatile u8 svcNumber = 0;
int main(void)
{
	SYSCNTRL_vidEnableGPIOClock(GPIO_PORTF);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_GREEN,GPIO_OUTPUT);
	__asm("SVC #254");
	
	while(1);

}

__attribute__ ((naked)) void SVC_Handler(void)
{
 __asm("MRS R0,MSP");
 __asm("B SVC_Handler_c");
}

void SVC_Handler_c(u32 * pBaseOfStackFrame)
{
	GPIO_vidSetPinValue(GPIO_PORTF,GPIO_LED_GREEN,STD_HIGH);
	u8 * ptrReturnAddress = (u8*) pBaseOfStackFrame[6];
	ptrReturnAddress-=2;
	svcNumber = *ptrReturnAddress;
	
}