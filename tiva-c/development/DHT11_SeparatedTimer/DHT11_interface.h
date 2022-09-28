#ifndef _DHT11_INTERFACE_H
#define _DHT11_INTERFACE_H

/*Function declarations*/
void DHT11_vidInit(TIMERHandle_t * timerHandle);
void DHT11_vidStart(void);
u8 DHT11_u8CheckResponse(void);
u8 DHT11_u8ReadByte(void);
static void delayUs(u32 ui32Us);
void delayMs(u32 ui32Ms);

/*Macros*/
#define DHT11_RESPONSE_GOOD 1
#define DHT11_RESPONSE_BAD 0


#endif