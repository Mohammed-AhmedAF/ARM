#ifndef _I2C_INTERFACE_H
#define _I2C_INTERFACE_H

typedef struct
{
	u8 u8Module;
	u8 u8Mode;
	u8 u8TimerPeriod;
	u8 u8Loopback;
	u8 u8Interrupt;
	void (*ptrFun) (void);
}I2CConfig;	

/*Function declaration*/
/*General*/
void I2C_vidInit(I2CConfig const * i2Config);
void I2C_vidClearInterrupt(u8 u8Module,u8 u8InterruptID);

/*I2C0*/
void I2C0_vidInit(I2CConfig const * i2cConfig);
u8 I2C0_u8SendByte(u8 u8SlaveAddress,u8 u8MemAddress,u8 u8Byte);
u32 I2C0_u32SendMultipleBytes(u32 u32SlaveAddress,u8 * u8ptData, u8 u8DataSize);
void I2C0_vidPutISRFunction(void (*ptrF) (void));
void I2C0_vidClearInterrupt(u8 u8InterruptID);
u32 I2C0_u32WaitTillDone(void);

/*I2C1*/
void I2C1_vidInit(I2CConfig const * i2cConfig);
u8 I2C1_u8SendByte(u8 u8SlaveAddress,u8 u8MemAddress,u8 u8Byte);
u8 I2C1_u8SendByteWithSlaveAddressOnly(u8 u8SlaveAddress, u8 u8Byte);
u32 I2C1_u32SendMultipleBytes(u32 u32SlaveAddress,u8 * u8ptData, u8 u8DataSize);
void I2C1_vidPutISRFunction(void (*ptrF) (void));
void I2C1_vidClearInterrupt(u8 u8InterruptID);
u32 I2C1_u32WaitTillDone(void);

/*I2C2*/
void I2C2_vidInit(I2CConfig const * i2cConfig);
u8 I2C2_u8SendByte(u8 u8SlaveAddress,u8 u8MemAddress,u8 u8Byte);
void I2C2_vidSendMultipleBytes(u8 * u8ptData, u8 u8DataSize);
void I2C2_vidPutISRFunction(void (*ptrF) (void));
void I2C2_vidClearInterrupt(u8 u8InterruptID);
u32 I2C2_u32WaitTillDone(void);

/*I2C3*/
void I2C3_vidInit(I2CConfig const * i2cConfig);
u8 I2C3_u8SendByte(u8 u8SlaveAddress, u8 u8MemAddress,u8 u8DataByte);
u32 I2C3_u32SendMultipleBytes(u32 u32SlaveAddress,u8 * u8ptData, u8 u8DataSize);
void I2C3_vidPutISRFunction(void (*ptrF) (void));
void I2C3_vidClearInterrupt(u8 u8InterruptID);
u32 I2C3_u32WaitTillDone(void);

/*Function handler definitions*/
void I2C0_Handler(void);
void I2C1_Handler(void);
void I2C2_Handler(void);
void I2C3_Handler(void);


/*Macros*/
#define I2C_MODULE_0 0
#define I2C_MODULE_1 1
#define I2C_MODULE_2 2
#define I2C_MODULE_3 3
#define I2C_MODE_MASTER 0
#define I2C_MODE_SLAVE 1
#define I2C_INTERRUPT_MIM_ENABLED (1<<0)
#define I2C_INTERRUPT_MIM_DISABLED 0
#define I2C_INTERRUPT_CLKIM_ENABLED (1<<1)
#define I2C_INTERRUPT_CLKIM_DISABLED 0

#define I2C_INTERRUPT_MIM_ID 0
#define I2C_INTERRUPT_CLKIM_ID 1

#define I2C_SPEED_100K 100000

#define I2C_LOOPBACK_DISABLED 0
#define I2C_LOOPBACK_ENABLED 1

#define I2C_CALC(SysClk,speed) ((SysClk/(20*speed))-1)

#endif