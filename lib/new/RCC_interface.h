/***************************************************************************/
/* Author : Mohammed Ahmed                                                 */
/* Version: V01                                                            */
/* Date: 16 April 2021                                                     */
/***************************************************************************/
#ifndef _RCC_INTERFACE_H
#define _RCC_INTERFACE_H

#define RCC_AHB 0
#define RCC_APB1 1
#define RCC_APB2 2

void RCC_voidInitSysClock(void);
void RCC_voidEnableClock(u8 Copy_u8BusId,u8 Copy_u8PerId);
void RCC_voidDisableClock(u8 Copy_u8BusId,u8 Copy_u8PerId);

#endif