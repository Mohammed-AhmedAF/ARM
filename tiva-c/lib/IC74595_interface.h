#ifndef _IC74595_INTERFACE_H
#define _IC74595_INTERFACE_H

typedef struct
{
	u8 u8LatchPort;
	u8 u8LatchPin;
	u8 u8OutEnPort;
	u8 u8OutEnPin;
} IC74595Config_t;

void IC74595_vidInit(IC74595Config_t * IC74595Config);
void IC74595_vidControl(IC74595Config_t * config);

#endif