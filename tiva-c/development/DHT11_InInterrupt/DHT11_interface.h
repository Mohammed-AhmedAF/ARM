#ifndef _DHT11_INTERFACE_H
#define _DHT11_INTERFACE_H

/*Function declarations*/
void DHT11_vidInit(void);
void DHT11_vidStart(void);
u8 DHT11_u8CheckResponse(void);
u8 DHT11_u8ReadByte(void);
u8 * DHT11_ptU8GetData(u8 * ptrU8DataArr);

/*Pin definition*/
#define DHT11_PORT GPIO_PORTB
#define DHT11_PIN GPIO_PIN5

#define DHT11_SUCCESS 0xF1
#define DHT11_FAILURE 0xF0

#endif