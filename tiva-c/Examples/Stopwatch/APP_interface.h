#ifndef _APP_INTERFACE_H
#define _APP_INTERFACE_H

#define APP_COUNT_UP 1
#define APP_COUNT_DOWN 2
#define APP_COUNT_STOP 0

void vidBlink(void);
void vidCountDown(void);
void vidProcessCommand(void);
void vidResetStopWatch(void);
void vidProcessButtons(void);

#endif