#ifndef _I2C_INTERFACE_H
#define _I2C_INTERFACE_H

typedef struct
{
	u8 u8Mode;
	u8 u8TimerPeriod;
	u8 u8Interrupt;
	void (*ptrFun) (void);
}I2CConfig;	

/*Function declaration*/
/*I2C0*/
void I2C0_vidInit(I2CConfig * i2cConfig);
u8 I2C0_u8SendByte(u8 u8Byte);
void I2C0_vidSendMultipleBytes(u8 * u8ptData, u8 u8DataSize);
void I2C0_vidPutISRFunction(void (*ptrF) (void));
void I2C0_vidClearInterrupt(u8 u8InterruptID);

/*I2C1*/
void I2C1_vidInit(I2CConfig * i2cConfig);
u8 I2C1_u8SendByte(u8 u8Byte);
void I2C1_vidSendMultipleBytes(u8 * u8ptData, u8 u8DataSize);
void I2C1_vidPutISRFunction(void (*ptrF) (void));
void I2C1_vidClearInterrupt(u8 u8InterruptID);

/*I2C2*/
void I2C2_vidInit(I2CConfig * i2cConfig);
u8 I2C2_u8SendByte(u8 u8Byte);
void I2C2_vidSendMultipleBytes(u8 * u8ptData, u8 u8DataSize);
void I2C2_vidPutISRFunction(void (*ptrF) (void));
void I2C2_vidClearInterrupt(u8 u8InterruptID);

/*I2C3*/
void I2C3_vidInit(I2CConfig * i2cConfig);
u8 I2C3_u8SendByte(u8 u8Byte);
void I2C3_vidSendMultipleBytes(u8 * u8ptData, u8 u8DataSize);
void I2C3_vidPutISRFunction(void (*ptrF) (void));
void I2C3_vidClearInterrupt(u8 u8InterruptID);

/*Macros*/
#define I2C_MODE_MASTER 0
#define I2C_MODE_SLAVE 1
#define I2C_INTERRUPT_RIS_ENABLED 1
#define I2C_INTERRUPT_RIS_DISABLED 0
#define I2C_INTERRUPT_CLKIM_ENABLED 2
#define I2C_INTERRUPT_CLKIM_DISABLED 3

#define I2C_INTERRUPT_RIS_ID 0
#define I2C_INTERRUPT_CLKIM_ID 1

#define I2C_SPEED_100K 100000

#define I2C_CALC(SysClk,speed) ((SysClk/(20*speed))-1)

#endif