/* 
 * Author: Mohamed Ahmed Abd Al-Fattah
 * Purpose: 16x2 LCD driver for stm32f103c8t6 MCU
 */

#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MDIO_interface.h"
#include "ELCD_interface.h"

u16 i = 0;
void ELCD_vidInit(void) {
	/*Setting configuration for data pins*/
	MDIO_vidSetPinConfiguration(ELCD_D0_PORT,ELCD_D0_PIN,MDIO_GPOUT_PP);
	MDIO_vidSetPinConfiguration(ELCD_D1_PORT,ELCD_D1_PIN,MDIO_GPOUT_PP);
	MDIO_vidSetPinConfiguration(ELCD_D2_PORT,ELCD_D2_PIN,MDIO_GPOUT_PP);
	MDIO_vidSetPinConfiguration(ELCD_D3_PORT,ELCD_D3_PIN,MDIO_GPOUT_PP);
	MDIO_vidSetPinConfiguration(ELCD_D4_PORT,ELCD_D4_PIN,MDIO_GPOUT_PP);
	MDIO_vidSetPinConfiguration(ELCD_D5_PORT,ELCD_D5_PIN,MDIO_GPOUT_PP);
	MDIO_vidSetPinConfiguration(ELCD_D6_PORT,ELCD_D6_PIN,MDIO_GPOUT_PP);
	MDIO_vidSetPinConfiguration(ELCD_D7_PORT,ELCD_D7_PIN,MDIO_GPOUT_PP);

	/*Setting Mode for data pins*/
	MDIO_vidSetPinMode(ELCD_D0_PORT,ELCD_D0_PIN,MDIO_OUTSPEED_10);
	MDIO_vidSetPinMode(ELCD_D1_PORT,ELCD_D1_PIN,MDIO_OUTSPEED_10);
	MDIO_vidSetPinMode(ELCD_D2_PORT,ELCD_D2_PIN,MDIO_OUTSPEED_10);
	MDIO_vidSetPinMode(ELCD_D3_PORT,ELCD_D3_PIN,MDIO_OUTSPEED_10);
	MDIO_vidSetPinMode(ELCD_D4_PORT,ELCD_D4_PIN,MDIO_OUTSPEED_10);
	MDIO_vidSetPinMode(ELCD_D5_PORT,ELCD_D5_PIN,MDIO_OUTSPEED_10);
	MDIO_vidSetPinMode(ELCD_D6_PORT,ELCD_D6_PIN,MDIO_OUTSPEED_10);
	MDIO_vidSetPinMode(ELCD_D7_PORT,ELCD_D7_PIN,MDIO_OUTSPEED_10);

	/*Setting configuration for command pins*/
	MDIO_vidSetPinConfiguration(ELCD_RS_PORT,ELCD_RS_PIN,MDIO_GPOUT_PP);
	MDIO_vidSetPinConfiguration(ELCD_RW_PORT,ELCD_RW_PIN,MDIO_GPOUT_PP);
	MDIO_vidSetPinConfiguration(ELCD_EN_PORT,ELCD_EN_PIN,MDIO_GPOUT_PP);
	/*Setting mode for command pins*/
	MDIO_vidSetPinMode(ELCD_RS_PORT,ELCD_RS_PIN,MDIO_OUTSPEED_10);
	MDIO_vidSetPinMode(ELCD_RW_PORT,ELCD_RW_PIN,MDIO_OUTSPEED_10);
	MDIO_vidSetPinMode(ELCD_EN_PORT,ELCD_EN_PIN,MDIO_OUTSPEED_10);


	/*Giving initialization commands*/
	ELCD_vidSendCommand(ELCD_CLEAR_SCREEN); /*Clear screen*/
	ELCD_vidSendCommand(ELCD_RETURN_HOME); /*Move to home*/
	ELCD_vidSendCommand(0b00000110); /*Set entry mode*/
	ELCD_vidSendCommand(0b00001100); /*Display On/Off control*/
	ELCD_vidSendCommand(0b00110000); /*Function Set*/
}

void ELCD_vidSendCommand(u8 u8commandCpy) {
	MDIO_vidSetPinValue(ELCD_RS_PORT,ELCD_RS_PIN,STD_LOW);
	MDIO_vidSetPinValue(ELCD_RW_PORT,ELCD_RW_PIN,STD_LOW);

	MDIO_vidSetPinValue(ELCD_D0_PORT,ELCD_D0_PIN,GET_BIT(u8commandCpy,0));
	MDIO_vidSetPinValue(ELCD_D1_PORT,ELCD_D1_PIN,GET_BIT(u8commandCpy,1));
	MDIO_vidSetPinValue(ELCD_D2_PORT,ELCD_D2_PIN,GET_BIT(u8commandCpy,2));
	MDIO_vidSetPinValue(ELCD_D3_PORT,ELCD_D3_PIN,GET_BIT(u8commandCpy,3));
	MDIO_vidSetPinValue(ELCD_D4_PORT,ELCD_D4_PIN,GET_BIT(u8commandCpy,4));
	MDIO_vidSetPinValue(ELCD_D5_PORT,ELCD_D5_PIN,GET_BIT(u8commandCpy,5));
	MDIO_vidSetPinValue(ELCD_D6_PORT,ELCD_D6_PIN,GET_BIT(u8commandCpy,6));
	MDIO_vidSetPinValue(ELCD_D7_PORT,ELCD_D7_PIN,GET_BIT(u8commandCpy,7));

	MDIO_vidSetPinValue(ELCD_EN_PORT,ELCD_EN_PIN,STD_HIGH);
	for(i = 0; i < 16000; i++);
	MDIO_vidSetPinValue(ELCD_EN_PORT,ELCD_EN_PIN,STD_LOW);
	for (i = 0; i<16000; i++);
	MDIO_vidSetPinValue(ELCD_EN_PORT,ELCD_EN_PIN,STD_HIGH);	

}

void ELCD_vidWriteCharacter(u8 u8CharacterCpy) {
	MDIO_vidSetPinValue(ELCD_RS_PORT,ELCD_RS_PIN,STD_HIGH);
	MDIO_vidSetPinValue(ELCD_RW_PORT,ELCD_RW_PIN,STD_LOW);

	MDIO_vidSetPinValue(ELCD_D0_PORT,ELCD_D0_PIN,GET_BIT(u8CharacterCpy,0));
	MDIO_vidSetPinValue(ELCD_D1_PORT,ELCD_D1_PIN,GET_BIT(u8CharacterCpy,1));
	MDIO_vidSetPinValue(ELCD_D2_PORT,ELCD_D2_PIN,GET_BIT(u8CharacterCpy,2));
	MDIO_vidSetPinValue(ELCD_D3_PORT,ELCD_D3_PIN,GET_BIT(u8CharacterCpy,3));
	MDIO_vidSetPinValue(ELCD_D4_PORT,ELCD_D4_PIN,GET_BIT(u8CharacterCpy,4));
	MDIO_vidSetPinValue(ELCD_D5_PORT,ELCD_D5_PIN,GET_BIT(u8CharacterCpy,5));
	MDIO_vidSetPinValue(ELCD_D6_PORT,ELCD_D6_PIN,GET_BIT(u8CharacterCpy,6));
	MDIO_vidSetPinValue(ELCD_D7_PORT,ELCD_D7_PIN,GET_BIT(u8CharacterCpy,7));

	MDIO_vidSetPinValue(ELCD_EN_PORT,ELCD_EN_PIN,STD_HIGH);
	for(i = 0; i < 16000; i++);
	MDIO_vidSetPinValue(ELCD_EN_PORT,ELCD_EN_PIN,STD_LOW);
	for(i = 0; i < 16000; i++);
	MDIO_vidSetPinValue(ELCD_EN_PORT,ELCD_EN_PIN,STD_HIGH);	
}

void ELCD_vidWriteString(u8 * u8StringPtrCpy) {
	while (*u8StringPtrCpy != '\0') {
		ELCD_vidWriteCharacter(*u8StringPtrCpy);
		u8StringPtrCpy++;
	}

}

void ELCD_vidWriteNumber(u16 u16NumberCpy) {
	if(u16NumberCpy < 10) {
		ELCD_vidWriteCharacter(u16NumberCpy+'0');
	}
	else {
		if (u16NumberCpy < 100) {
			ELCD_vidWriteCharacter(u16NumberCpy/10+'0');
			ELCD_vidWriteCharacter(u16NumberCpy%10+'0');
		}
		else if  (u16NumberCpy < 1000) {
			ELCD_vidWriteCharacter(u16NumberCpy/100+'0');
			ELCD_vidWriteCharacter((u16NumberCpy%100)/10+'0');
			ELCD_vidWriteCharacter((u16NumberCpy%100)%10+'0');
		}
		else if (u16NumberCpy < 10000) {
			ELCD_vidWriteCharacter((u16NumberCpy/1000)+'0');
			ELCD_vidWriteCharacter((u16NumberCpy%1000)/100+'0');
			ELCD_vidWriteCharacter(((u16NumberCpy%1000)%100)%10+'0');
			ELCD_vidWriteCharacter((u16NumberCpy%1000)%10+'0');
		}
	}
}

void ELCD_vidGoToXY(s8 s8xCpy, s8 s8yCpy) {
	if (s8yCpy == 1) {
			ELCD_vidSendCommand(0x80+s8xCpy);
	}
	else {
			ELCD_vidSendCommand(0xC0+s8xCpy);
	}
}

