#ifndef _DHT11_INTERFACE_H
#define _DHT11_INTERFACE_H

/*Function declarations*/
void DHT11_vidInit(void);
void DHT11_vidStart(void);
u8 DHT11_u8CheckResponse(void);
u8 DHT11_u8ReadByte(void);
static void delayUs(u32 ui32Us);
void delayMs(u32 ui32Ms);
/*Pin definition*/
#define DHT11_PORT GPIO_PORTB
#define DHT11_PIN GPIO_PIN5



#endif