#include "STD_TYPES.h"
#include "Macros.h"
#include "I2C_private.h"
#include "I2C_interface.h"
#include "TM4C123GH6PM.h"


char I2C1_write(int slaveAddr, char memAddr, char data)
{
	char error;
	
	I2C1->MSA = slaveAddr << 1;
	I2C1->MDR = memAddr;
	I2C1->MCS = 3;
	
	error = I2C1_wait_till_done();
	if (error) return error;
	
	/*Send data*/
	I2C1->MDR = data;
	I2C1->MCS = 5;
	error = I2C1_wait_till_done();
	while(I2C1->MCS & 0x40);
	error = I2C1->MCS & 0xE;
	if (error) return error;
	
	return 0;
	
	
}

void I2C1_vidInit(void)
{
	SYSCTL->RCGCI2C |= 0x02;
	
	
	GPIOA->AFSEL |= 0xC0;
	GPIOA->PCTL &= ~0xFF000000;
	GPIOA->PCTL |= 0x33000000;
	
	GPIOA->DEN |= 0xC0;
	GPIOA->ODR |= 0x80;
	
	I2C1->MCR = 0x10;
	I2C1->MTPR = 7;
}

static int I2C1_wait_till_done(void)
{
	while(I2C1->MCS & 1);
	return I2C1->MCS & 0xE;
	
}

char I2C1_read(int slaveAddr, char memAddr, int byteCount, u8 * data)
{
	char error;
	
	if (byteCount <= 0)
	{
		return -1;
	}
	
	I2C1->MSA = slaveAddr << 1;
	I2C1->MDR = memAddr;
	I2C1->MCS = 3;
	
	error = I2C1_wait_till_done();
	if (error)
	{
		return error;
	}
	
		I2C1->MSA = (slaveAddr << 1) + 1;
		
		if (byteCount == 1)
		{
			I2C1->MCS = 7;
		}
		else {
			I2C1->MCS = 0xB;
		}	
				error = I2C1_wait_till_done();
			if (error) return error;
	
		*data++ = I2C1->MDR;
		
		if (--byteCount == 0)
		{
			while(I2C1->MCS & 0x40);
			return 0;
		}
		
		while(byteCount > 1)
		{
			I2C1->MCS = 9;
			error = I2C1_wait_till_done();
			if (error)  return error;
			byteCount--;
			*data++ = I2C1->MDR;
		}
		
		I2C1->MCS = 5;
		error = I2C1_wait_till_done();
		*data = I2C1->MDR;
		while(I2C1->MCS & 0x40);
		
		return 0; /*No error*/
		
}
