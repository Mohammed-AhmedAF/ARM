#ifndef _ELCD_INTERFACE_H
#define _ELCD_INTERFACE_H

void ELCD_vidInit(void);
void ELCD_vidSendCommand(u8 u8CommandCpy);
void ELCD_vidWriteCharacter(u8 u8CharacterCpy);
void ELCD_vidWriteString(u8 * u8StringPtrCpy);


/*Data port definitions*/
#define ELCD_D0_PORT MDIO_PORTA
#define ELCD_D1_PORT MDIO_PORTA
#define ELCD_D2_PORT MDIO_PORTA
#define ELCD_D3_PORT MDIO_PORTA
#define ELCD_D4_PORT MDIO_PORTA
#define ELCD_D5_PORT MDIO_PORTA
#define ELCD_D6_PORT MDIO_PORTA
#define ELCD_D7_PORT MDIO_PORTA

/*Command port definitions*/
#define ELCD_RS_PORT MDIO_PORTA
#define ELCD_RW_PORT MDIO_PORTA
#define ELCD_EN_PORT MDIO_PORTA

/*Data pin definitions*/
#define ELCD_D0_PIN MDIO_PIN0
#define ELCD_D1_PIN MDIO_PIN1
#define ELCD_D2_PIN MDIO_PIN2
#define ELCD_D3_PIN MDIO_PIN3
#define ELCD_D4_PIN MDIO_PIN4
#define ELCD_D5_PIN MDIO_PIN5
#define ELCD_D6_PIN MDIO_PIN6
#define ELCD_D7_PIN MDIO_PIN7

/*Command pin definitions*/
#define ELCD_RS_PIN MDIO_PIN8
#define ELCD_RW_PIN MDIO_PIN9
#define ELCD_EN_PIN MDIO_PIN10

/*Definitions of LCD commands*/
#define ELCD_CLEAR_SCREEN 0x00
#define ELCD_RETURN_HOME 0x01


#endif
