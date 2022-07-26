#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "MAX7219_config.h"
#include "MAX7219_interface.h"

void MAX7219_vidInit(void)
{
	/*Chip select*/
	GPIO_vidSetPinDigEnable(MAX7219_CS_PORT,MAX7219_CS_PIN,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(MAX7219_CS_PORT,MAX7219_CS_PIN,GPIO_DIR_OUTPUT);
	
	/*Clock*/
	GPIO_vidSetPinDigEnable(MAX7219_CLK_PORT,MAX7219_CLK_PIN,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(MAX7219_CLK_PORT,MAX7219_CLK_PIN,GPIO_DIR_OUTPUT);
	
	/*Data input*/
	GPIO_vidSetPinDigEnable(MAX7219_DIN_PORT,MAX7219_DIN_PIN,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(MAX7219_DIN_PORT,MAX7219_DIN_PIN,GPIO_DIR_OUTPUT);

	MAX7219_vidWriteMax(0x09,0x00);
	MAX7219_vidWriteMax(0x0a,0x03);
	MAX7219_vidWriteMax(0x0b,0x07);
	MAX7219_vidWriteMax(0x0c,0x01);
	MAX7219_vidWriteMax(0x0f,0x00);

	MAX7219_vidClear();

}

void MAX7219_vidWriteByte(u8 u8Byte)
{
	for (u8 u8Index = 0; u8Index <8 ; u8Index++)
	{
		/*Pull CLK down*/
		GPIO_vidSetPinValue(MAX7219_CLK_PORT,MAX7219_CLK_PIN,0);
		/*Write the MSB*/
		GPIO_vidSetPinValue(MAX7219_DIN_PORT,MAX7219_DIN_PIN, u8Byte&0x80);
		u8Byte = u8Byte<<1;
		/*Pull CLK up*/
		GPIO_vidSetPinValue(MAX7219_CLK_PORT,MAX7219_CLK_PIN,1);

	}
}

void MAX7219_vidWriteMax(u8 u8Address, u8 u8Data)
{
	/*Pull CS down*/
	GPIO_vidSetPinValue(MAX7219_CS_PORT,MAX7219_CS_PIN,0);
	
	/*Send address*/
	MAX7219_vidWriteByte(u8Address);

	/*Send data*/
	MAX7219_vidWriteByte(u8Data);
	
	/*Pull CS UP*/
	GPIO_vidSetPinValue(MAX7219_CS_PORT,MAX7219_CS_PIN,1);
}

void MAX7219_vidClear(void)
{
	MAX7219_vidWriteMax(0x01,0x00);
	MAX7219_vidWriteMax(0x02,0x00);
	MAX7219_vidWriteMax(0x03,0x00);
	MAX7219_vidWriteMax(0x04,0x00);
	MAX7219_vidWriteMax(0x05,0x00);
	MAX7219_vidWriteMax(0x06,0x00);
	MAX7219_vidWriteMax(0x07,0x00);
	MAX7219_vidWriteMax(0x08,0x00);
}

