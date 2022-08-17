#ifndef _TIMER1_PRIVATE_H
#define _TIMER1_PRIVATE_H
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

#define TIMER1  ((volatile TIMER_t *) 0x40031000UL)

#endif