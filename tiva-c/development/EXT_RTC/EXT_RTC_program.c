#include "STD_TYPES.h"
#include "Macros.h"
#include "I2C_interface.h"
#include "EXT_RTC_interface.h"
#include "UART_interface.h"

u8 EXT_RTC_DEC2BCD(u8 value)
{
	return (value + 6*(value/10));
}

u8 EXT_RTC_BCD2DEC(u8 value)
{
	return (value - 6*(value>>4));
}

void EXT_RTC_vidSetTime(RTC_t * const ptRTC)
{
	I2C1_u8SendByte(EXT_RTC_ADDRESS,ADDR_SECONDS,ptRTC->u8Seconds);
	I2C1_u8SendByte(EXT_RTC_ADDRESS,ADDR_MINUTES,ptRTC->u8Minutes);
	I2C1_u8SendByte(EXT_RTC_ADDRESS,ADDR_HOURS,ptRTC->u8Hours);
	
}

void EXT_RTC_vidSetDate(RTC_t * const ptRTC)
{
	I2C1_u8SendByte(EXT_RTC_ADDRESS,ADDR_DAY_OF_WEEK,ptRTC->u8DayOfWeek);
	I2C1_u8SendByte(EXT_RTC_ADDRESS,ADDR_DAYS,ptRTC->u8Days);
	I2C1_u8SendByte(EXT_RTC_ADDRESS,ADDR_MONTHS,ptRTC->u8Months);
	I2C1_u8SendByte(EXT_RTC_ADDRESS,ADDR_YEARS,ptRTC->u8Years);
}

void EXT_RTC_vidGetTime(RTC_t * ptRTC)
{
	ptRTC->u8Seconds = I2C1_u8GetByte(EXT_RTC_ADDRESS,ADDR_SECONDS);
	ptRTC->u8Minutes = I2C1_u8GetByte(EXT_RTC_ADDRESS,ADDR_MINUTES);
	ptRTC->u8Hours = I2C1_u8GetByte(EXT_RTC_ADDRESS,ADDR_HOURS);
}

void EXT_RTC_vidGetTime_test(RTC_t * ptRTC)
{
	I2C1_u8SendByteWithSlaveAddressOnly(0x68,0);
	
	I2C1_u8SendByteWithSlaveAddressOnly(0x68,0xD1);

	ptRTC->u8Seconds = I2C1_u8ReceiveWithAck();
	ptRTC->u8Minutes = I2C1_u8ReceiveWithAck();
	ptRTC->u8Hours = I2C1_u8ReceiveWithAck();

	I2C1_vidSendStop();
}

void EXT_RTC_vidGetDate(RTC_t * ptRTC)
{
	ptRTC->u8DayOfWeek = EXT_RTC_BCD2DEC(I2C1_u8GetByte(EXT_RTC_ADDRESS,ADDR_DAY_OF_WEEK));
	ptRTC->u8Days = EXT_RTC_BCD2DEC(I2C1_u8GetByte(EXT_RTC_ADDRESS,ADDR_DAYS));
	ptRTC->u8Months = EXT_RTC_BCD2DEC(I2C1_u8GetByte(EXT_RTC_ADDRESS,ADDR_MONTHS));
	ptRTC->u8Years = EXT_RTC_BCD2DEC(I2C1_u8GetByte(EXT_RTC_ADDRESS,ADDR_YEARS));

}

u8 EXT_RTC_u8GetDayOfWeek(void)
{
	return I2C1_u8GetByte(0x68,0);
}