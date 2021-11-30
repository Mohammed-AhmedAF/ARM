#include "STD_TYPES.h"
#include "Macros.h"
#include "I2C_private.h"
#include "I2C_interface.h"
#include "TM4C123GH6PM.h"


static void (*ptrFI2C0) (void);
static void (*ptrFI2C1) (void);
static void (*ptrFI2C2) (void);
static void (*ptrFI2C3) (void);

void I2C0_vidInit(I2CConfig * i2cConfig)
{
	/*Mode: Master or Slave*/
	switch(i2cConfig->u8Mode)
	{
		case I2C_MODE_MASTER:
			SET_BIT(I2C0->MCR,4);
			break;
		case I2C_MODE_SLAVE:
			CLEAR_BIT(I2C0->MCR,4);
			break;
	}

	/*Calculation of timer period*/
	/*100,000 kbps*/
	I2C0->MTPR = i2cConfig->u8TimerPeriod;
	
	/*Interrupt configuration*/
//	if (i2cConfig->u8Interrupt == I2C_INTERRUPT_RIS_ENABLED)
//	{
//		SET_BIT(I2C0->MIMR,0);
//	}
//	else
//	{
//		CLEAR_BIT(I2C0->MIMR,0);
//	}
	
	/*Adding handler*/
//	if ((i2cConfig->u8Interrupt == I2C_INTERRUPT_RIS_ENABLED)
//		|| (i2cConfig->u8Interrupt == I2C_INTERRUPT_CLKIM_ENABLED))
//	{
//		I2C0_vidPutISRFunction(i2cConfig->ptrFun);
//	}
	
}

void I2C1_vidInit(I2CConfig * i2cConfig)
{
/*Mode: Master or Slave*/
	switch(i2cConfig->u8Mode)
	{
		case I2C_MODE_MASTER:
			SET_BIT(I2C1->MCR,4);
			break;
		case I2C_MODE_SLAVE:
			CLEAR_BIT(I2C1->MCR,4);
			break;
	}

	
	/*Calculation of timer period*/
	/*100,000 kbps*/
	I2C1->MTPR = i2cConfig->u8TimerPeriod;
}

void I2C2_vidInit(I2CConfig * i2cConfig)
{
/*Mode: Master or Slave*/
	switch(i2cConfig->u8Mode)
	{
		case I2C_MODE_MASTER:
			SET_BIT(I2C2->MCR,4);
			break;
		case I2C_MODE_SLAVE:
			CLEAR_BIT(I2C2->MCR,4);
			break;
	}

	
	/*Calculation of timer period*/
	/*100,000 kbps*/
	I2C2->MTPR = i2cConfig->u8TimerPeriod;
}

void I2C3_vidInit(I2CConfig * i2cConfig)
{
/*Mode: Master or Slave*/
	switch(i2cConfig->u8Mode)
	{
		case I2C_MODE_MASTER:
			SET_BIT(I2C3->MCR,4);
			break;
		case I2C_MODE_SLAVE:
			CLEAR_BIT(I2C3->MCR,4);
			break;
	}

	
	/*Calculation of timer period*/
	/*100,000 kbps*/
	I2C0->MTPR = i2cConfig->u8TimerPeriod;
}

void I2C0_vidSendByte(u8 u8Byte)
{
	/*Slave address*/
	/*Bit0 specifies R/W*/
	I2C0->MSA |= 2<<1;

	/*Data to be sent*/
	I2C0->MDR = u8Byte;
	
	/*STOP START RUN*/
	I2C0->MCS = (I2C_CNTRL_RUN | I2C_CNTRL_START | I2C_CNTRL_STOP);
	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C0->MCS,0) == 1);
}

void I2C0_vidPutISRFunction(void (*ptrF) (void))
{
	ptrFI2C0 = ptrF;
}

void I2C1_vidSendByte(u8 u8Byte)
{
	/*Slave address*/
	/*Bit0 specifies R/W*/
	I2C1->MSA |= 2<<1;

	/*Data to be sent*/
	I2C1->MDR = u8Byte;
	
	/*STOP START RUN*/
	I2C1->MCS |= (I2C_CNTRL_RUN | I2C_CNTRL_START | I2C_CNTRL_STOP);
	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C1->MCS,0) == 1);
}

void I2C2_vidSendByte(u8 u8Byte)
{
	/*Slave address*/
	/*Bit0 specifies R/W*/
	I2C2->MSA |= 2<<1;

	/*Data to be sent*/
	I2C2->MDR = u8Byte;
	
	/*STOP START RUN*/
	I2C2->MCS |= (I2C_CNTRL_RUN | I2C_CNTRL_START | I2C_CNTRL_STOP);
	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C2->MCS,0) == 1);
}

void I2C3_vidSendByte(u8 u8Byte)
{
	/*Slave address*/
	/*Bit0 specifies R/W*/
	I2C3->MSA |= 2<<1;

	/*Data to be sent*/
	I2C3->MDR = u8Byte;
	
	/*STOP START RUN*/
	I2C3->MCS |= (I2C_CNTRL_RUN | I2C_CNTRL_START | I2C_CNTRL_STOP);
	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C3->MCS,0) == 1);
}

void I2C0_vidSendMultipleBytes(u8 * u8ptData, u8 u8DataSize)
{

	/*Slave address*/
	/*Bit0 specifies R/W*/
	I2C0->MSA |= 2<<1;

	/*First byte to be sent*/
	I2C0->MDR = *u8ptData;
	u8DataSize--;
	/*START RUN*/
	I2C0->MCS |= (I2C_CNTRL_RUN | I2C_CNTRL_START | I2C_CNTRL_ACK);
	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C0->MCS,0) == 1);
	
	/*Sending rest of bytes*/
	while (u8DataSize > 1)
	{
	I2C0->MDR = *u8ptData++;
	u8DataSize--;
	/*RUN*/
	I2C0->MCS |= (I2C_CNTRL_RUN | I2C_CNTRL_ACK);
	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C0->MCS,0) == 1);
	}
		
	/*Sending the last byte*/
	I2C0->MDR = *u8ptData++;
	I2C0->MCS |= (I2C_CNTRL_RUN | I2C_CNTRL_STOP);

	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C0->MCS,0) == 1);
	
}


void I2C0_vidClearInterrupt(u8 u8InterruptID)
{
	if (u8InterruptID == I2C_INTERRUPT_RIS_ID)
	{
		SET_BIT(I2C0->MICR,0);
	}
	else if(u8InterruptID == I2C_INTERRUPT_CLKIM_ID)
	{
		SET_BIT(I2C0->MICR,1);
	}
}

void I2C0_Handler()
{
	ptrFI2C0();
}

void I2C1_Handler()
{
	ptrFI2C1();
}

void I2C2_Handler()
{
	ptrFI2C2();
}

void I2C3_Handler()
{
	ptrFI2C3();
}