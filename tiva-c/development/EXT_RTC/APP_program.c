#include "Macros.h"
#include "STD_TYPES.h"
#include "SYSCNTRL_interface.h"
#include "GPIO_interface.h"
#include "SysTick_interface.h"
#include "I2C_interface.h"
#include "UART_interface.h"
#include "DHT11_interface.h"
#include "PCF8574_interface.h"
#include "EXT_RTC_interface.h"
#include "LCD_interface.h"
#include "APP_interface.h"
#include "MAX7219_interface.h"

static u8 u8Message[]={'H','e','l','l','o'};

static void vidI2C0Handler(void);

void vidI2C0Handler(void)
{
	//GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);
	I2C_vidClearInterrupt(I2C_MODULE_1,I2C_INTERRUPT_MIM_ID);
}

void vidBlinkOnSysTick(void)
{		
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_RED);
		APP_vidDisplayTime();
}

void APP_MAX7219_vidInit(void)
{
	MAX7219_vidInit();

}


void APP_SYSTICK_vidInitialize(void)
{
	SysTickConfig_t sysTickConfig;
	sysTickConfig.ptrFunc = vidBlinkOnSysTick;
	sysTickConfig.u32ReloadValue = 16000000;
	sysTickConfig.u8ClockSource = SYSTICK_SYSTEM_CLOCK;
	sysTickConfig.u8Interrupt = SYSTICK_INTERRUPT_ENABLED;
	
	SysTick_vidInitExtended(&sysTickConfig);
	SysTick_vidStart();
}

void APP_I2C0_GPIO_vidInit(void)
{
	/*Clock control*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	SYSCNTRL_vidEnableI2CClock(SYSCNTRL_I2C_0);

	/*GPIO configuration*/
	GPIO_vidUnlock(GPIO_PORTB);
	GPIO_vidCommit(GPIO_PORTB,GPIO_PIN2);
	GPIO_vidCommit(GPIO_PORTB,GPIO_PIN3);
	GPIO_vidLock(GPIO_PORTB);
	
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN2);
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN3);
	
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN2,0x3);
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN3,0x3);
	
	GPIO_vidEnablePinOpenDrain(GPIO_PORTB,GPIO_PIN3);	
}

void APP_I2C1_GPIO_vidInit(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableI2CClock(SYSCNTRL_I2C_1);
	
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN6);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN7);
	
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN6,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN7,GPIO_DEN_SET);
	
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN6,0x3);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN7,0x3);
	
	GPIO_vidEnablePinOpenDrain(GPIO_PORTA,GPIO_PIN7);

}

void APP_I2C2_GPIO_vidInit(void)
{
	/*Clock control*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTE);
	SYSCNTRL_vidEnableI2CClock(SYSCNTRL_I2C_2);

	/*I2C2 control*/
	GPIO_vidSelectAlterFunction(GPIO_PORTE,GPIO_PIN4);
	GPIO_vidSelectAlterFunction(GPIO_PORTE,GPIO_PIN5);
	GPIO_vidSetPinDigEnable(GPIO_PORTE,GPIO_PIN4,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTE,GPIO_PIN5,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTE,GPIO_PIN4,0x3);
	GPIO_vidConfigPortControl(GPIO_PORTE,GPIO_PIN5,0x3);
	GPIO_vidEnablePinOpenDrain(GPIO_PORTE,GPIO_PIN5);
	
}

void APP_I2C3_GPIO_vidInit(void)
{
	/*Clock control*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTD);
	SYSCNTRL_vidEnableI2CClock(SYSCNTRL_I2C_3);
	
	/*I2C3 pins GPIO configuration*/
  GPIO_vidSelectAlterFunction(GPIO_PORTD,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTD,GPIO_PIN1);
  GPIO_vidSetPinDigEnable(GPIO_PORTD,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTD,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTD,GPIO_PIN0,0x3);
	GPIO_vidConfigPortControl(GPIO_PORTD,GPIO_PIN1,0x3);
	GPIO_vidEnablePinOpenDrain(GPIO_PORTD,GPIO_PIN1);
}

void APP_UART0_vidInit(void)
{
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	/*UART pins configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN0,GPIO_INPUT);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x1);
	
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN1,0x1);
	
	UARTConfig_t uart0Config;
	uart0Config.u8Module = UART_MODULE_0;
	uart0Config.u8ClockSource = UART_CLOCKSOURCE_RC;
	uart0Config.u8RxTx = UART_RXTX_BOTH;
	uart0Config.u8HighSpeedEnabled = UART_HIGHSPEED_DIV16;
	uart0Config.u8StopBits = UART_STOPBITS_1;
	uart0Config.u8WordLength = UART_WORDSIZE_8;
	uart0Config.u16Integer = 104;
	uart0Config.u8Fraction = 11;
	UART_vidInit(&uart0Config);
}

void APP_vidGetTemperature(void)
{
	static u8 u8RH1 = 0;
	static u8 u8RH2 = 0;
	static u8 u8Temp1 = 0;
	static u8 u8Temp2 = 0;
	static u8 u8Checksum = 0;
	
	u8RH1 = 0;
	u8RH2 = 0;
	u8Temp1 = 0;
	u8Temp2 = 0;
	u8Checksum = 0;
	DHT11_vidStart();

	if(DHT11_u8CheckResponse() == DHT11_RESPONSE_GOOD)
	{

		u8RH1 = DHT11_u8ReadByte();
		u8RH2 = DHT11_u8ReadByte();
		u8Temp1 = DHT11_u8ReadByte();
		u8Temp2 = DHT11_u8ReadByte();
		u8Checksum = DHT11_u8ReadByte();
		
	if ((u8RH1 + u8RH2 + u8Temp1 + u8Temp2) == u8Checksum)
	{
		UART0_vidSendString("Checksum: Good.\r\n");
	}
	else 
	{
		UART0_vidSendString("Checksum: Bad.\r\n");
	}
	
		UART0_vidSendString("Temperature: ");
		UART_vidSendNumber(UART0_vidSendByte,u8Temp1);
		UART0_vidSendString(" C");
		UART0_vidSendByte('\r');
		UART0_vidSendByte('\n');
		UART0_vidSendString("Humidity: ");
		UART_vidSendNumber(UART0_vidSendByte,u8RH1);
		UART0_vidSendString("%");
		UART0_vidSendByte('\r');
		UART0_vidSendByte('\n');
	
	}
	else
	{
		UART0_vidSendString("Error: Response.\r\n");
	}
}

void APP_I2C_Periph_vidInit(u8 u8Periph)
{
	/*UART pins configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN0,GPIO_INPUT);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x1);
	
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN1,0x1);
	
	/*GPIO configuration*/
	APP_I2C1_GPIO_vidInit();
	
	/*I2C Configuration*/
	I2CConfig i2cConfig;
	i2cConfig.u8Module = I2C_MODULE_1;
	i2cConfig.u8Mode = I2C_MODE_MASTER;
	i2cConfig.u8Loopback = I2C_LOOPBACK_DISABLED;
	i2cConfig.u8TimerPeriod = I2C_CALC(16000000,I2C_SPEED_100K);
	i2cConfig.u8Interrupt |= I2C_INTERRUPT_MIM_ENABLED;
	i2cConfig.ptrFun = vidI2C0Handler;
	I2C_vidInit(&i2cConfig);
}



void APP_vidDisplayTime(void)
{
		u8 rtcData[7];
		RTC_t	strcRTC;
		I2C1_u8ReadBytes(0x68,0,7,rtcData);
		UART_vidSendNumber(UART0_vidSendByte,EXT_RTC_BCD2DEC(rtcData[1]));
		UART0_vidSendByte('\r');
		UART0_vidSendByte('\n');

//	I2C1_u8ReadBytes(EXT_RTC_ADDRESS,0,7,rtcData);
//	strcRTC.u8Seconds = EXT_RTC_BCD2DEC(rtcData[ADDR_SECONDS]);
//	UART0_vidSendString("Seconds: ");
//	UART_vidSendNumber(UART0_vidSendByte,strcRTC.u8Seconds);
//	UART0_vidSendString("\r\n");
//	strcRTC.u8Minutes = EXT_RTC_BCD2DEC(rtcData[ADDR_MINUTES]);
//	UART0_vidSendString("Minutes: ");
//	UART_vidSendNumber(UART0_vidSendByte,strcRTC.u8Minutes);
//	UART0_vidSendString("\r\n");
//	strcRTC.u8Hours = EXT_RTC_BCD2DEC(rtcData[ADDR_HOURS]);
//	UART0_vidSendString("Hours: ");
//	UART_vidSendNumber(UART0_vidSendByte,strcRTC.u8Hours);
//	UART0_vidSendString("\r\n");
	
}

void APP_vidSetTime(void)
{
	
}