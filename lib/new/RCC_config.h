/***************************************************************************/
/* Author : Mohammed Ahmed                                                 */
/* Version: V01                                                            */
/* Date: 16 April 2021                                                     */
/***************************************************************************/
#ifndef _RCC_CONFIG_H
#define _RCC_CONFIG_H

#define RCC_CLK_TYPE RCC_HSE_CRYSTAL

/*Options:
    RCC_PLL_IN_HSI_DIV_2
    RCC_PLL_IN_HSE_DIV_2
    RCC_PLL_IN_HSE

*/

#if RCC_CLK_TYPE == RCC_PLL
#define RCC_PLL_INPUT 
#endif

/*Options 2 to 16*/
#if RCC_CLK_TYPE == RCC_PLL
#define RCC_PLL_MUL_VAL 4
#endif 

#endif