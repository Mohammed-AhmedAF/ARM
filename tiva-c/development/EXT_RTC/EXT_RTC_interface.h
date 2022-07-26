#ifndef _EXT_RTC_INTERFACE_H
#define _EXT_RTC_INTERFACE_H

typedef struct 
{
	u8 u8Seconds;
	u8 u8Minutes;
	u8 u8Hours;
	u8 u8DayOfWeek;
	u8 u8Days;
	u8 u8Months;
	u8 u8Years;
} RTC_t;

/*Macros*/
#define EXT_RTC_MODE_WRITE 0xD0
#define EXT_RTC_MODE_READ 0xD1
#define EXT_RTC_ADDRESS 0x68

typedef enum{
	ADDR_SECONDS = 0,
	ADDR_MINUTES = 1,
	ADDR_HOURS = 2,
	ADDR_DAY_OF_WEEK = 3,
	ADDR_DAYS = 4,
	ADDR_MONTHS = 5,
	ADDR_YEARS = 6
}rtc_addresses_t;

/*Function defintions*/
void EXT_RTC_vidInit(void);
void EXT_RTC_vidSetTime(RTC_t * const ptRTC);
void EXT_RTC_vidGetTime(RTC_t * ptRTC);
void EXT_RTC_vidSetDate(RTC_t * const ptRTC);
void EXT_RTC_vidGetDate(RTC_t * ptRTC);
void EXT_RTC_vidSetDayOfWeek(RTC_t * const ptRTC);
void EXT_RTC_vidGetDayOfWeek(RTC_t * ptRTC);
u8 EXT_RTC_DEC2BCD(u8 value);
u8 EXT_RTC_BCD2DEC(u8 value);
void EXT_RTC_vidGetTime_test(RTC_t * ptRTC);
u8 EXT_RTC_u8GetDayOfWeek(void);

#endif