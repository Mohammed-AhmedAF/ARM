#ifndef _MNVK_INTERFACE_H
#define _MNVK_INTERFACE_H

void MNVK_vidEnableInterrupt(u8 ID);
void MNVK_vidDisableInterrupt(u8 ID);
void MNVK_vidSetPendingFlag(u8 ID);
void MNVK_vidClearPendingFlag(u8 ID);

#endif
