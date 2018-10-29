#ifndef _CLOCK_INTERFACE_H
#define _CLOCK_INTERFACE_H

#include "LSTD_TYPES.h"
#include "Macros.h"
#include "ELCD_interface.h"

#define SHIFT 4

/*Function prototypes*/
void vidCount(void);
void vidInitClock(void);
void vidIncrementHour(void);
void vidIncrementMinute(void);
void vidCheckMinute(u8);
void vidSetAlarm(void);

#endif
