/***************************************************************************/
/* Author : Mohammed Ahmed                                                 */
/* Version: V01                                                            */
/* Date: 16 April 2021                                                     */
/***************************************************************************/
#include "STD_TYPES.h"
#include "Macros.h"
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

void RCC_voidInitSysClock(void)
{
    #if RCC_CLK_TYPE == RCC_HSE_CRYSTAL
        RCC_CR = 0x00010000;
        RCC_CFGR = 0x00000001;
    #elif RCC_CLK_TYPE == RCC_HSE_RC
        RCC_CR = 0x00050000;
        RCC_CFGR = 0x00000001;
    #elif RCC_CLK_TYPE == RCC_HSI
        RCC_CR = 0x00000001; /*Enable HSI, trimming = 0*/
        RCC_CFGR = 0x00000000;
    #elif RCC_CLK_TYPE == RCC_PLL
        #if RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2
            SET_BIT(RCC_CFGR,16);
        #elif  RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2

        #elif RCC_PLL_INPUT ==  RCC_PLL_IN_HSE

		#endif
    
    
    #else
        #error("You chose a wrong clock type.")

    #endif


    
}


void RCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
    if (Copy_u8PerId <= 31)
    {
        switch(Copy_u8BusId)
        {
            case RCC_AHB:
            SET_BIT(RCC_AHBENR,Copy_u8PerId);
            break;
            case RCC_APB1:
            SET_BIT(RCC_APB1ENR,Copy_u8PerId);
            break;
            case RCC_APB2:
            SET_BIT(RCC_APB2ENR,Copy_u8PerId);
            break;
            default:
            /*Return error code*/
            break;

        }

    }
    else
    {

        //Return error code
    }

}

void RCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
    if (Copy_u8PerId <= 31)
    {
        switch(Copy_u8BusId)
        {
            case RCC_AHB:
            CLEAR_BIT(RCC_AHBENR,Copy_u8PerId);
            break;
            case RCC_APB1:
            CLEAR_BIT(RCC_APB1ENR,Copy_u8PerId);
            break;
            case RCC_APB2:
            CLEAR_BIT(RCC_APB2ENR,Copy_u8PerId);
            break;
            default:
            	break;
            /*Return error code*/

        }

    }
    else
    {

        //Return error code
    }
}

void RCC_vidResetPeripheral(u8 u8Bus, u8 u8PeripheralID)
{
	switch(u8Bus)
	{
		case RCC_APB1:
			SET_BIT(RCC_APB1RSTR,u8PeripheralID);
			break;
		case RCC_APB2:
			SET_BIT(RCC_APB2RSTR,u8PeripheralID);
			break;
	}
}
