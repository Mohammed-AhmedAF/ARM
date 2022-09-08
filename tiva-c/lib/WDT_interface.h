#ifndef _WTD_INTERFACE_H
#define _WTD_INTERFACE_H

typedef struct 
{
	u32 u32Load;
	u8 u8InterruptType;
	u8 u8Reset;
	void (*ptrFHandler) (void);
}WDTConfig_t;


void WDT0_vidInit(const WDTConfig_t * WDTConfig);
void WDT0_vidEnable(void);
void WDT0_vidClearInterrupt(void);

/*ISR declaration*/
void WDT0_Handler(void);

/*Macros*/
#define WDT_INTERRUPT_STANDARD 0
#define WDT_INTERRUPT_NONMASKABLE 1

#endif