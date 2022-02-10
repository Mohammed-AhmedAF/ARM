#ifndef _MNVK_INTERFACE_H
#define _MNVK_INTERFACE_H

void NVIC_vidEnableInterrupt(u8 ID);
void NVIC_vidDisableInterrupt(u8 ID);
void NVIC_vidSetPendingFlag(u8 ID);
void NVIC_vidClearPendingFlag(u8 ID);

#endif
