#ifndef _I2C_PRIVATE_H
#define _I2C_PRIVATE_H

typedef struct
{
	volatile u32 MSA;
	volatile u32 MCS;
	volatile u32 MDR;
	volatile u32 TPR;
	volatile u32 MIMR;
	volatile u32 MRIS;
	volatile u32 MMIS;
	volatile u32 MICR;
	volatile u32 MCR;
	volatile u32 MCLKONCT;
	volatile u32 MBMON;
	volatile u32 MCR2;
	
}I2C_TYPE;


#define I2C0 ((I2C_TYPE*) 0x40020000)
#define I2C1 ((I2C_TYPE*) 0x40021000)
#define I2C2 ((I2C_TYPE*) 0x40022000)
#define I2C3 ((I2C_TYPE*) 0x40023000)

/*Macros used in driver*/
#define I2C_CNTRL_ACK 0x08
#define I2C_CNTRL_STOP 0x04
#define I2C_CNTRL_START 0x02
#define I2C_CNTRL_RUN 0x01

#endif
