#include "Macros.h"
#include "STD_TYPES.h"
#include "SYSCNTRL_interface.h"
#include "SCHEDULER_interface.h"

int main(void)
{

		SCHEDULER_vidInit(SCHEDULER_TICKSOURCE_SYSTICK);
	
	while(1)
	{
		SCHEDULER_vidDispatch();
	};
}