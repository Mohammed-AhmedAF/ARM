#ifndef _ROTENC_INTERFACE_H
#define _ROTENC_INTERFACE_H

typedef struct
{
	u8 u8ClockPort;
	u8 u8ClockPin;
	u8 u8DataPort;
	u8 u8DataPin;
	void (*ptrFSwitch) (void);
} ROTENCConfig_t;

typedef struct
{
	u8 u8Counter;
	u8 u8Direction;
} ROTENCRead_t;


void ROTENC_vidInit(ROTENCConfig_t const * pStrctROTENCConfig);
ROTENCRead_t ROTENC_strctGetReading(ROTENCConfig_t const * config);
void ROTENC_strctGetReading_tech(ROTENCConfig_t const * config);

#define ROTENC_DIR_CCW 0
#define ROTENC_DIR_CW 1
#define ROTENC_DIR_UNDEF 2

#endif