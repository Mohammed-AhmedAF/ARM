/***************************************************************************/
/* Author : Mohammed Ahmed                                                 */
/* Version: V01                                                            */
/* Date: 16 April 2021                                                     */
/***************************************************************************/
#include "STD_TYPES.h"
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

void RCC_voidEInitSysClock(void)
{
    #if RCC_CLK_TYPE == RCC_HSE_CRYSTAL
        RCC_CFGR = 0x00010000;
    #elif RCC_CLK_TYPE == RCC_HSE_RC
        RCC_CFGR = 0x00005000;
    #elif RCC_CLK_TYPE == RCC_HSI
        RCC_CFGR = 0x00000081; /*Enable HSI, trimming = 0*/
    #elif RCC_CLK_TYPE == RCC_PLL
    
    
    #else
        #error("You chose a wrong clock type.")

    #endif


    
}


void RCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
    if (Copy_u8PerId <= 31)
    {
        swtich(Copy_u8BusId)
        {
            case RCC_AHB:
            SET_BIT(RCC_AHBENR,Copy_u8PerId);
            break;
            case RCC_APB1:
            SET_BIT(RCC_AHBENR,Copy_u8PerId);
            break;
            case RCC_APB2:
            break;
            default:
            /*Return error code*/

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
        swtich(Copy_u8BusId)
        {
            case RCC_AHB:
            CLEAR_BIT(RCC_AHBENR,Copy_u8PerId);
            break;
            case RCC_APB1:
            CLEAR_BIT(RCC_APB1ENR,Copy_u8PerId);
            break;
            case RCC_APB2:
            CLEAR_BIT(RCC_APB2ENR,Copy_u8PerId)
            break;
            default:
            /*Return error code*/

        }

    }
    else
    {

        //Return error code
    }

}