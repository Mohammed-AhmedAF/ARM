#include "Macros.h"
#include "STD_TYPES.h"
#include "I2C_interface.h"
#include "PCF8574_config.h"
#include "PCF8574_interface.h"

void PCF8574_vidSendByte(u8 u8Byte)
{
	I2C1_u8SendByteWithSlaveAddressOnly(PCF8574_ADDRESS,u8Byte);
}