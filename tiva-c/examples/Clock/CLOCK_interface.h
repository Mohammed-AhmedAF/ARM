#ifndef _CLOCK_INTERFACE_H
#define _CLOCK_INTERFACE_H

void CLOCK_vidCount(void);
void CLOCK_vidIncrementHours(void);
void CLOCK_vidIncrementMinutes(void);
void CLOCK_vidCheckAlarm(void);
void CLOCK_vidSetClock(void);

#define CLOCK_ALARM_CLEARED 0
#define CLOCK_ALARM_SET 1
#define CLOCK_SEC_OVFCOUNT 1000

#endif

