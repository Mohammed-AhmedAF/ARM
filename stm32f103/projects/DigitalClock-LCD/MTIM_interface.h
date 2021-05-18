#ifndef _MTIM_INTERFACE_H
#define _MTIM_INTERFACE_H

void MTIM_vidInit();
void MTIM_vidPutFunction(void (*ptrF) (void));

/*Register bits definitions*/
#define MTIM_CR1_CEN 0
#define MTIM_CR1_DIR 4


#define MTIM_DIER_UIE 0

#endif
