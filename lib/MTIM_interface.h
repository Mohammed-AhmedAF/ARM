#ifndef _MTIM_INTERFACE_H
#define _MTIM_INTERFACE_H

void MTIM_vidInit();
u16 MTIM_u16GetCount();

/*Register bits definitions*/
#define MTIM_CR1_CEN 0
#define MTIM_CR1_DIR 4

#endif
