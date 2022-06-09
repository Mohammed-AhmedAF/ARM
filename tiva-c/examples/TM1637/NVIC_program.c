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


void NVIC_vidSetPending(u8 u8InterruptID)
{
if (u8InterruptID < 32)
	{
		NVIC->ISPR[0] |= (1<<u8InterruptID);
	}
	else if ((u8InterruptID >= 32) & (u8InterruptID < 63))
	{
		NVIC->ISPR[1] |= (1<<(u8InterruptID-32));
	}
}

void NVIC_vidClearPending(u8 u8InterruptID)
{
if (u8InterruptID < 32)
	{
		NVIC->ICPR[0] |= (1<<u8InterruptID);
	}
	else if ((u8InterruptID >= 32) & (u8InterruptID < 63))
	{
		NVIC->ICPR[1] |= (1<<(u8InterruptID-32));
	}
}

u8 NVIC_u8GetPending(u8 u8InterruptID)
{
	u8 u8PendingResult = 0;
	if (u8InterruptID < 32)
	{
		u8PendingResult = GET_BIT(NVIC->ISPR[0],u8InterruptID);
	}
	else if ((u8InterruptID >= 32) & (u8InterruptID < 63))
	{
		u8PendingResult = GET_BIT(NVIC->ISPR[1],u8InterruptID);
	}
	
	return u8PendingResult;
}

void NVIC_vidSetPriority(u8 u8InterruptID, u8 u8InterruptPriority)
{
	NVIC->IP[u8InterruptID] = (u8InterruptPriority<<5);
}