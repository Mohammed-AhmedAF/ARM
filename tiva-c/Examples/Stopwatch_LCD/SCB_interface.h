#ifndef _SCB_INTERFACE_H
#define _SCB_INTERFACE_H

/*Function declarations*/
void SCB_vidEnterSleepMode(u8 u8SleepMode);

#define SCB_SLEEPMODE_SLEEP 1
#define SCB_SLEEPMODE_DEEP 2
#define SCB_SLEEPMODE_HYPERNATION 3


#endif