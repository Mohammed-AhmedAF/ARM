#ifndef _IC74595_INTERFACE_H
#define _IC74595_INTERFACE_H

typedef struct
{
	u8 u8LatchPort;
	u8 u8LatchPin;
	u8 u8OutEnPort;
	u8 u8OutEnPin;
	u8 u8ClearPort;
	u8 u8ClearPin;
} IC74595Config_t;

void IC74595_vidInit(IC74595Config_t * IC74595Config);
void IC74595_vidControl(IC74595Config_t * config);
void IC74595_vidClear(IC74595Config_t * config);
void IC74595_vidTest(IC74595Config_t * config, u8 u8Byte);

#endif