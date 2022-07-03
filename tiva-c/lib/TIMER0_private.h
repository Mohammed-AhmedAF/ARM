#ifndef _TIMER0_PRIVATE_H
#define _TIMER0_PRIVATE_H

typedef struct{
 u32  CFG;                               /*!< GPTM Configuration                                                    */
 u32  TAMR;                              /*!< GPTM Timer A Mode                                                     */
 u32  TBMR;                              /*!< GPTM Timer B Mode                                                     */
 u32  CTL;                               /*!< GPTM Control                                                          */
 u32  SYNC;                              /*!< GPTM Synchronize                                                      */
 u32  RESERVED;
 u32  IMR;                               /*!< GPTM Interrupt Mask                                                   */
 u32  RIS;                               /*!< GPTM Raw Interrupt Status                                             */
 u32  MIS;                               /*!< GPTM Masked Interrupt Status                                          */
 u32  ICR;                               /*!< GPTM Interrupt Clear                                                  */
 u32  TAILR;                             /*!< GPTM Timer A Interval Load                                            */
 u32  TBILR;                             /*!< GPTM Timer B Interval Load                                            */
 u32  TAMATCHR;                          /*!< GPTM Timer A Match                                                    */
 u32  TBMATCHR;                          /*!< GPTM Timer B Match                                                    */
 u32  TAPR;                              /*!< GPTM Timer A Prescale                                                 */
 u32  TBPR;                              /*!< GPTM Timer B Prescale                                                 */
 u32  TAPMR;                             /*!< GPTM TimerA Prescale Match                                            */
 u32  TBPMR;                             /*!< GPTM TimerB Prescale Match                                            */
 u32  TAR;                               /*!< GPTM Timer A                                                          */
 u32  TBR;                               /*!< GPTM Timer B                                                          */
 u32  TAV;                               /*!< GPTM Timer A Value                                                    */
 u32  TBV;                               /*!< GPTM Timer B Value                                                    */
 u32  RTCPD;                             /*!< GPTM RTC Predivide                                                    */
 u32  TAPS;                              /*!< GPTM Timer A Prescale Snapshot                                        */
 u32  TBPS;                              /*!< GPTM Timer B Prescale Snapshot                                        */
 u32  TAPV;                              /*!< GPTM Timer A Prescale Value                                           */
 u32  TBPV;                              /*!< GPTM Timer B Prescale Value                                           */
 u32  RESERVED1[981];
 u32  PP;
} TIMER_t;	

#define TIMER0  ((volatile TIMER_t *) 0x40030000UL)

#define TIM0_CFG * ((u32*) 0x40030000)
#define TIM0_TAMR * ((u32*) 0x40030004)
#define TIM0_TBMR * ((u32*) 0x40030008)
#define TIM0_CTL * ((u32 * const) 0x4003000C)
#define TIM0_SYNC * ((u32*) 0x40030010)
#define TIM0_IMR * ((u32*) 0x40030018)
#define TIM0_RIS * ((u32*) 0x4003001C)
#define TIM0_MIS * ((u32*) 0x40030020)
#define TIM0_ICR * ((u32*) 0x40030024)
#define TIM0_TAILR * ((u32*) 0x40030028)
#define TIM0_TBILR * ((u32*) 0x4003002C)
#define TIM0_TAMATCHR * ((u32*) 0x40030030)
#define TIM0_TBMATCHR * ((u32*) 0x40030034)
#define TIM0_TAPR * ((u32*) 0x40030038)
#define TIM0_TBPR * ((u32*) 0x4003003C)
#define TIM0_TAPMR * ((u32*) 0x40030040)
#define TIM0_TBPMR * ((u32*) 0x40030044)
#define TIM0_TAR * ((u32*) 0x40030048)
#define TIM0_TBR * ((u32*) 0x4003004C)
#define TIM0_TAV * ((u32*) 0x40030050)
#define TIM0_TBV * ((u32*) 0x40030054)
#define TIM0_RTCPD * ((u32*) 0x40030058)
#define TIM0_TAPS * ((u32*) 0x4003005C)
#define TIM0_TBPS * ((u32*) 0x40030060)
#define TIM0_TAPV * ((u32*) 0x40030064)
#define TIM0_TBPV * ((u32*) 0x40030068)
#define TIM0_PP * ((u32*) 0x40030FC0)
#endif