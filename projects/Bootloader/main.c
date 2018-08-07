#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MDIO_interface.h"
#include "MRCC_interface.h"
#include "MRCC_private.h"
#include "MUART_interface.h"
#include "ELCD_interface.h"

void vidParser(void);

/*Pointer to the main of application*/
void (*ptrFunc)(void);

void main(void) {
	MRCC_vidInit();
	MRCC_vidEnableClock(BUS_APB2, PERIPHERAL_GPIOA);
	MRCC_vidEnableClock(BUS_APB2, PERIPHERAL_GPIOB);
	SET_BIT(MRCC->APB2ENR, 14);
	MDIO_vidInit();

	MDIO_vidSetPinConfiguration(MDIO_PORTA, MDIO_PIN9, MDIO_AFOUT_PP);
	MDIO_vidSetPinConfiguration(MDIO_PORTA, MDIO_PIN10, MDIO_GPINPUT_F);

	MDIO_vidSetPinMode(MDIO_PORTA, MDIO_PIN9, MDIO_OUTSPEED_2);
	MDIO_vidSetPinMode(MDIO_PORTA, MDIO_PIN10, MDIO_INPUTMODE);

	ELCD_vidInit();
	MUART_vidInit();
	ELCD_vidSendCommand(ELCD_CLEAR_SCREEN);


	while (1) {
		vidParser();
	}

}

void vidParser(void) {
	u8 length[2];
	u8 data[32];
	u8 address[4];
	u8 type[2];
	u8 c, i;
	u16 lineCount = 0;
	u16 dataRecordsCount = 0;
	while (1) {
		c = MUART_u8ReceiveByte();
		if (c == ':') {
			lineCount++;
			/*Length*/
			for (i = 0; i < 2; i++) {
				length[i] = MUART_u8ReceiveByte();
				/*MUART_vidSendByte(length[i]);*/
			}
			/*Address*/
			for (i = 0; i < 4; i++) {
				address[i] = MUART_u8ReceiveByte();
				/*MUART_vidSendByte(address[i]); */
			}
			/*Type*/
			for (i = 0; i < 2; i++) {
				type[i] = MUART_u8ReceiveByte();
				/* MUART_vidSendByte(type[i]); */
			}
			/*Data*/
			if (length[0] == '1' && length[1] == '0')
			{
				dataRecordsCount++;
				for (i = 0; i < 32; i++) {
					data[i] = MUART_u8ReceiveByte();
					MUART_vidSendByte(data[i]);
				}
			} else if (length[0] == '0' && length[1] == '2') {
				for (i = 0; i < 4; i++) {
					data[i] = MUART_u8ReceiveByte();
					MUART_vidSendByte(data[i]);
				}
			} else if (length[0] == '0' && length[1] == '4') {
				for (i = 0; i < 8; i++) {
					data[i] = MUART_u8ReceiveByte();
					MUART_vidSendByte(data[i]);
				}
			} else if (length[0] == '0' && length[1] == '8') {
				for (i = 0; i < 16; i++) {
					data[i] = MUART_u8ReceiveByte();
					MUART_vidSendByte(data[i]);
				}
			} else if (length[0] == '0' && length[1] == 'C') {
				for (i = 0; i < 24; i++) {
					data[i] = MUART_u8ReceiveByte();
					MUART_vidSendByte(data[i]);
				}
			} else if (length[0] == '0' && length[1] == '0') {
				ELCD_vidWriteNumber(lineCount);
				ELCD_vidWriteCharacter(' ');
				ELCD_vidWriteNumber(dataRecordsCount);
				break;
			}
			/*Get checksum*/
			for (i = 0; i < 2; i++) {
				MUART_vidSendByte(MUART_u8ReceiveByte());
			}
			MUART_vidSendByte('\r');
			MUART_vidSendByte('\n');
		}

	}
}
