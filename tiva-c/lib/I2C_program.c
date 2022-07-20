#include "STD_TYPES.h"
#include "Macros.h"
#include "I2C_private.h"
#include "I2C_interface.h"


static void (*ptrFI2C0) (void) = NULL;
static void (*ptrFI2C1) (void) = NULL;
static void (*ptrFI2C2) (void) = NULL;
static void (*ptrFI2C3) (void) = NULL;

void I2C_vidInit(I2CConfig const * i2Config)
{
	switch(i2Config->u8Module)
	{
		case I2C_MODULE_0:
			I2C0_vidInit(i2Config);
			break;
		case I2C_MODULE_1:
			I2C1_vidInit(i2Config);
			break;
		case I2C_MODULE_2:
			I2C2_vidInit(i2Config);
			break;
		case I2C_MODULE_3:
			I2C3_vidInit(i2Config);
			break;
	}
}

void I2C_vidClearInterrupt(u8 u8Module, u8 u8InterruptID)
{
	switch(u8Module)
	{
		case I2C_MODULE_0:
			I2C0_vidClearInterrupt(u8InterruptID);
			break;
		case I2C_MODULE_1:
			I2C1_vidClearInterrupt(u8InterruptID);
			break;
		case I2C_MODULE_2:
			I2C2_vidClearInterrupt(u8InterruptID);
			break;
		case I2C_MODULE_3:
			I2C3_vidClearInterrupt(u8InterruptID);
			break;
	}
}


void I2C0_vidInit(I2CConfig const * i2cConfig)
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
//	else if (i2cConfig->u8Interrupt == I2C_INTERRUPT_RIS_DISABLED)
//	{
//		CLEAR_BIT(I2C0->MIMR,0);
//	}
//	
//	/*Adding handler*/
//	if ((i2cConfig->u8Interrupt == I2C_INTERRUPT_RIS_ENABLED)
//		|| (i2cConfig->u8Interrupt == I2C_INTERRUPT_CLKIM_ENABLED))
//	{
//		I2C0_vidPutISRFunction(i2cConfig->ptrFun);
//	}
	
}

void I2C1_vidInit(I2CConfig const * i2cConfig)
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
	
	/*Check interrupt configuration*/
	/*Master Interrupt Mask*/
	if (GET_BIT(i2cConfig->u8Interrupt,0))
	{
		SET_BIT(I2C1->MIMR,0);
		ptrFI2C1 = i2cConfig->ptrFun;
	}
	else
	{
		CLEAR_BIT(I2C1->MIMR,0);
	}
	
	/*Clock Timeout Interrupt Mask*/
	if (GET_BIT(i2cConfig->u8Interrupt,1))
	{
		SET_BIT(I2C1->MIMR,1);
	}
	else
	{
		CLEAR_BIT(I2C1->MIMR,1);
	}
	
	/*Loopback*/
	if (i2cConfig->u8Loopback)
	{
		SET_BIT(I2C1->MCR,0);
	}
	else
	{
		CLEAR_BIT(I2C1->MCR,0);
	}
}

void I2C2_vidInit(I2CConfig const * i2cConfig)
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
	
	/*Check interrupt configuration*/
	/*Master Interrupt Mask*/
	if (GET_BIT(i2cConfig->u8Interrupt,0))
	{
		SET_BIT(I2C2->MIMR,0);
		ptrFI2C2 = i2cConfig->ptrFun;
	}
	else
	{
		CLEAR_BIT(I2C2->MIMR,0);
	}
	
	/*Clock Timeout Interrupt Mask*/
	if (GET_BIT(i2cConfig->u8Interrupt,1))
	{
		SET_BIT(I2C2->MIMR,1);
	}
	else
	{
		CLEAR_BIT(I2C2->MIMR,1);
	}
	
	/*Loopback*/
	if (i2cConfig->u8Loopback)
	{
		SET_BIT(I2C2->MCR,0);
	}
	else
	{
		CLEAR_BIT(I2C2->MCR,0);
	}
}

void I2C3_vidInit(I2CConfig const * i2cConfig)
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
	I2C3->MTPR = i2cConfig->u8TimerPeriod;
	
	
	/*Check interrupt configuration*/
	/*Master Interrupt Mask*/
	if (GET_BIT(i2cConfig->u8Interrupt,0))
	{
		SET_BIT(I2C3->MIMR,0);
		ptrFI2C3 = i2cConfig->ptrFun;
	}
	else
	{
		CLEAR_BIT(I2C3->MIMR,0);
	}
	
	/*Clock Timeout Interrupt Mask*/
	if (GET_BIT(i2cConfig->u8Interrupt,1))
	{
		SET_BIT(I2C3->MIMR,1);
	}
	else
	{
		CLEAR_BIT(I2C3->MIMR,1);
	}
	
	/*Loopback*/
	if (i2cConfig->u8Loopback)
	{
		SET_BIT(I2C3->MCR,0);
	}
	else
	{
		CLEAR_BIT(I2C3->MCR,0);
	}
	
}


u32 I2C0_u32WaitTillDone(void)
{
	while(I2C0->MCS & 1);
	return I2C0->MCS & 0xE;
}

u32 I2C1_u32WaitTillDone(void)
{
	while(I2C1->MCS & 1);
	return I2C1->MCS & 0xE;
}

u32 I2C2_u32WaitTillDone(void)
{
	while(I2C2->MCS & 1);
	return I2C2->MCS & 0xE;
}

u32 I2C3_u32WaitTillDone(void)
{
	while (I2C3->MCS & 1);
	/*Return error code, 0 if no error*/
	return I2C3->MCS & 0xE;
}

u32 I2C0_u32SendMultipleBytes(u32 u32SlaveAddress,u8 * u8ptData, u8 u8DataSize)
{
	u32 u32Error;
	/*Slave address*/
	/*Bit0 specifies R/W*/
	I2C0->MSA |= u32SlaveAddress<<1;

	/*First byte to be sent*/
	I2C0->MDR = *u8ptData++;
	u8DataSize--;

	/*START RUN*/
	I2C0->MCS = I2C_CNTRL_START | I2C_CNTRL_RUN;
	
	/*Wait for the busy bit to become 0*/
	u32Error = I2C0_u32WaitTillDone();
	if (u32Error)
	{
		//return u32Error;
	}
	
	/*Sending rest of bytes*/
	while (u8DataSize > 1)
	{
		I2C0->MDR = *u8ptData++;
		/*RUN*/
		I2C0->MCS = I2C_CNTRL_RUN;
	
		/*Wait for the busy bit to become 0*/
		u32Error = I2C0_u32WaitTillDone();
		if (u32Error)
		{
			//return u32Error;
		}

		u8DataSize--;

	}
		
	/*Sending the last byte*/
	I2C0->MDR = *u8ptData++;
	I2C0->MCS = (I2C_CNTRL_RUN | I2C_CNTRL_STOP);

	u32Error = I2C0_u32WaitTillDone();

	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C0->MCS,6) == 1);
	
	if (u32Error)
	{
		//return u32Error;
	}

	return 0;
}

u32 I2C1_u32SendMultipleBytes(u32 u32SlaveAddress, u8 * u8ptData, u8 u8DataSize)
{
u32 u32Error;
	
	/*Slave address*/
	/*Bit0 specifies R/W*/
	I2C1->MSA |= u32SlaveAddress<<1;

	/*First byte to be sent*/
	I2C1->MDR = *u8ptData++;
	u8DataSize--;

	/*START RUN*/
	I2C1->MCS =	(I2C_CNTRL_START | I2C_CNTRL_RUN);
	
	/*Wait for the busy bit to become 0*/
	u32Error = I2C1_u32WaitTillDone();
	if (u32Error)
	{
		//return u32Error;
	}
	
	/*Sending rest of bytes*/
	while (u8DataSize > 1)
	{
		I2C1->MDR = *u8ptData++;
		/*RUN*/
		I2C1->MCS = I2C_CNTRL_RUN;
			
		/*Wait for the busy bit to become 0*/
		u32Error = I2C1_u32WaitTillDone();
		if (u32Error)
		{
			//return u32Error;
		}
			u8DataSize--;
	}
		
	/*Sending the last byte*/
	I2C1->MDR = *u8ptData++;
	I2C1->MCS = (I2C_CNTRL_RUN | I2C_CNTRL_STOP);

	u32Error = I2C1_u32WaitTillDone();
	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C1->MCS,6) == 1);
	
	if (u32Error)
	{
		//return u32Error;
	}
	
	return 0;
}

u32 I2C3_u32SendMultipleBytes(u32 u32SlaveAddress,u8 * u8ptData, u8 u8DataSize)
{
	u32 u32Error;
	
	/*Slave address*/
	/*Bit0 specifies R/W*/
	I2C3->MSA |= u32SlaveAddress<<1;

	/*First byte to be sent*/
	I2C3->MDR = *u8ptData++;
	u8DataSize--;

	/*START RUN*/
	I2C3->MCS =	(I2C_CNTRL_START | I2C_CNTRL_RUN);
	
	/*Wait for the busy bit to become 0*/
	u32Error = I2C3_u32WaitTillDone();
	if (u32Error)
	{
		//return u32Error;
	}
	
	/*Sending rest of bytes*/
	while (u8DataSize > 1)
	{
		I2C3->MDR = *u8ptData++;
		/*RUN*/
		I2C3->MCS = I2C_CNTRL_RUN;
			
		/*Wait for the busy bit to become 0*/
		u32Error = I2C3_u32WaitTillDone();
		if (u32Error)
		{
			//return u32Error;
		}
			u8DataSize--;
	}
		
	/*Sending the last byte*/
	I2C3->MDR = *u8ptData++;
	I2C3->MCS = (I2C_CNTRL_RUN | I2C_CNTRL_STOP);

	u32Error = I2C3_u32WaitTillDone();
	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C3->MCS,6) == 1);
	
	if (u32Error)
	{
		//return u32Error;
	}
	
	return 0;
}


void I2C0_vidClearInterrupt(u8 u8InterruptID)
{
	if (u8InterruptID == I2C_INTERRUPT_MIM_ID)
	{
		SET_BIT(I2C0->MICR,0);
	}
	else if(u8InterruptID == I2C_INTERRUPT_CLKIM_ID)
	{
		SET_BIT(I2C0->MICR,1);
	}
}

void I2C1_vidClearInterrupt(u8 u8InterruptID)
{
	if (u8InterruptID == I2C_INTERRUPT_MIM_ID)
	{
		SET_BIT(I2C1->MICR,0);
	}
	else if(u8InterruptID == I2C_INTERRUPT_CLKIM_ID)
	{
		SET_BIT(I2C1->MICR,1);
	}
}

void I2C2_vidClearInterrupt(u8 u8InterruptID)
{
	if (u8InterruptID == I2C_INTERRUPT_MIM_ID)
	{
		SET_BIT(I2C2->MICR,0);
	}
	else if(u8InterruptID == I2C_INTERRUPT_CLKIM_ID)
	{
		SET_BIT(I2C2->MICR,1);
	}
}

void I2C3_vidClearInterrupt(u8 u8InterruptID)
{
	if (u8InterruptID == I2C_INTERRUPT_MIM_ID)
	{
		SET_BIT(I2C3->MICR,0);
	}
	else if(u8InterruptID == I2C_INTERRUPT_CLKIM_ID)
	{
		SET_BIT(I2C3->MICR,1);
	}
}

u8 I2C0_u8SendByte(u8 u8SlaveAddress,u8 u8MemAddress,u8 u8Byte)
{
	/*Slave address*/
	/*Bit0 specifies R/W*/
	I2C0->MSA |= (u8SlaveAddress)<<1;

	/*Data to be sent*/
	I2C0->MDR = u8MemAddress;
	
	/*STOP START RUN*/
	I2C0->MCS = (I2C_CNTRL_RUN | I2C_CNTRL_START);
	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C0->MCS,0) == 1);
	
	/*Actual data*/
	I2C0->MDR = u8Byte;
	I2C0->MCS = (I2C_CNTRL_RUN | I2C_CNTRL_STOP);
	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C0->MCS,0) == 1);
	
	/*Check error bit*/
	return GET_BIT(I2C0->MCS,1);
}

u8 I2C1_u8SendByte(u8 u8SlaveAddress,u8 u8MemAddress,u8 u8Byte)
{
	/*Slave address*/
	/*Bit0 specifies R/W*/
	I2C1->MSA |= (u8SlaveAddress)<<1;

	/*Data to be sent*/
	I2C1->MDR = u8MemAddress;
	
	/*STOP START RUN*/
	I2C1->MCS = (I2C_CNTRL_RUN | I2C_CNTRL_START);
	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C1->MCS,0) == 1);
	
	/*Actual data*/
	I2C1->MDR = u8Byte;
	I2C1->MCS = (I2C_CNTRL_RUN | I2C_CNTRL_STOP);
	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C1->MCS,0) == 1);	
}

u8 I2C1_u8SendByteWithSlaveAddressOnly(u8 u8SlaveAddress, u8 u8Byte)
{
	/*Slave address*/
	/*Bit0 specifies R/W*/
	I2C1->MSA |= (u8SlaveAddress)<<1;

	/*Data to be sent*/
	I2C1->MDR = u8Byte;
	
	/*STOP START RUN*/
	I2C1->MCS = (I2C_CNTRL_RUN | I2C_CNTRL_START | I2C_CNTRL_STOP);
	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C1->MCS,0) == 1);
}

u8 I2C2_u8SendByte(u8 u8SlaveAddress,u8 u8MemAddress,u8 u8Byte)
{
	/*Slave address*/
	/*Bit0 specifies R/W*/
	I2C2->MSA |= (u8SlaveAddress)<<1;

	/*Data to be sent*/
	I2C2->MDR = u8MemAddress;
	
	/*STOP START RUN*/
	I2C2->MCS = (I2C_CNTRL_RUN | I2C_CNTRL_START);
	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C2->MCS,0) == 1);
	
	/*Actual data*/
	I2C2->MDR = u8Byte;
	I2C2->MCS = (I2C_CNTRL_RUN | I2C_CNTRL_STOP);
	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C2->MCS,0) == 1);
	
	/*Check error bit*/
	return GET_BIT(I2C2->MCS,1);
}

u8 I2C3_u8SendByte(u8 u8SlaveAddress, u8 u8MemAddress, u8 u8DataByte)
{
	/*Slave address*/
	/*Bit0 specifies R/W*/
	I2C3->MSA |= (u8SlaveAddress)<<1;

	/*Data to be sent*/
	I2C3->MDR = u8MemAddress;
	
	/*STOP START RUN*/
	I2C3->MCS = (I2C_CNTRL_RUN | I2C_CNTRL_START);
	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C3->MCS,0) == 1);
	
	/*Actual data*/
	I2C3->MDR = u8DataByte;
	I2C3->MCS = (I2C_CNTRL_RUN | I2C_CNTRL_STOP);
	
	/*Wait for the busy bit to become 0*/
	while(GET_BIT(I2C3->MCS,0) == 1);
	
	/*Check error bit*/
	return GET_BIT(I2C3->MCS,1);
}


void I2C0_Handler()
{
	if (ptrFI2C0 != NULL)
	{
		ptrFI2C0();
	}
}

void I2C1_Handler()
{
	if (ptrFI2C1 != NULL)
	{
		ptrFI2C1();
	}
}

void I2C2_Handler()
{
	if (ptrFI2C2 != NULL)
	{
		ptrFI2C2();
	}
}

void I2C3_Handler()
{
	if (ptrFI2C3 != NULL)
	{
		ptrFI2C3();
	}
}