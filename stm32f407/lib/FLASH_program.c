#include "Macros.h"
#include "Std_Types.h"
#include "FLASH_private.h"
#include "FLASH_interface.h"

void FLASH_vidUnlock(void)
{
    FLASH_KEYR = UNLOCK_KEY1;
    FLASH_KEYR = UNLOCK_KEY2;
}

void FLASH_vidErase(u8 u8Sector)
{
    /*Checking busy bit*/
    while(GET_BIT(FLASH_SR,16) == 1);

    /*Selecting which sector to erase*/
    switch (u8Sector)
    {
    case FLASH_SECTOR_0:
        FLASH_CR |= (FLASH_SECTOR_0<<3);
        break;
    case FLASH_SECTOR_1:
        FLASH_CR |= (FLASH_SECTOR_1<<3);
        break;
    case FLASH_SECTOR_2:
        FLASH_CR |= (FLASH_SECTOR_2<<3);
        break;
    case FLASH_SECTOR_3:
        FLASH_CR |= (FLASH_SECTOR_3<<3);
        break;
    case FLASH_SECTOR_4:
        FLASH_CR |= (FLASH_SECTOR_4<<3);
        break;
    case FLASH_SECTOR_5:
        FLASH_CR |= (FLASH_SECTOR_5<<3);
        break;
    case FLASH_SECTOR_6:
        FLASH_CR |= (FLASH_SECTOR_6<<3);
        break;
    case FLASH_SECTOR_7:
        FLASH_CR |= (FLASH_SECTOR_7<<3);
        break;
    case FLASH_SECTOR_ALL:
        /*Setting mass erase bit MER*/
        SET_BIT(FLASH_CR,2);
    default:
        break;
    }

    /*Setting start bit (STRT)*/
    SET_BIT(FLASH_CR,16);
    
    /*Checking busy bit*/
    while(GET_BIT(FLASH_SR,16));

}