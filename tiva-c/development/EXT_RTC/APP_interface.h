#ifndef _APP_INTERFACE_H
#define _APP_INTERFACE_H

void vidBlinkOnSysTick(void);
void APP_SYSTICK_vidInitialize(void);
void APP_I2C_Periph_vidInit(u8 u8Periph);
static void APP_I2C0_GPIO_vidInit(void);
static void APP_I2C1_GPIO_vidInit(void);
static void APP_I2C2_GPIO_vidInit(void);
static void APP_I2C3_GPIO_vidInit(void);
void APP_MAX7219_vidInit(void);
void APP_UART0_vidInit(void);
void APP_vidGetTemperature(void);
void APP_vidDisplayTime(void);
void APP_vidSetTime(void);
#endif