#include "STD_TYPES.h"
#include "Macros.h"
#include "SERVICES_interface.h"

void SERVICES_vidDelay(unsigned long counter)
{
	unsigned long count = 0;
	
	for(count=0; count < counter*1000; count++);
}
