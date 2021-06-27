#include "Macros.h"
#include "STD_TYPES.h"
#include "NVIC_interface.h"
#include "TM4C123.h"                    // Device header

void NVIC_vidSetInterrupt(u8 u8InterruptID)
{
	if (u8InterruptID < 32)
	{
		NVIC->ISER[0] |= (1<<u8InterruptID);
	}
	else if ((u8InterruptID >= 32) & (u8InterruptID < 63))
	{
		NVIC->ISER[1] |= (1<<(u8InterruptID-32));
	}
}

void NVIC_vidClearInterrupt(u8 u8InterruptID)
{
	if (u8InterruptID < 32)
	{
		NVIC->ICER[0] |= (1<<u8InterruptID);
	}
	else if ((u8InterruptID >= 32) & (u8InterruptID < 63))
	{
		NVIC->ICER[1] |= (1<<(u8InterruptID-32));
	}
}