#ifndef _WTD_PRIVATE_H
#define _WTD_PRIVATE_H

typedef struct {                          /*!< WATCHDOG0 Structure                                                   */
  u32  LOAD;                              /*!< Watchdog Load                                                         */
  u32  VALUE;                             /*!< Watchdog Value                                                        */
  u32  CTL;                               /*!< Watchdog Control                                                      */
  u32  ICR;                               /*!< Watchdog Interrupt Clear                                              */
  u32  RIS;                               /*!< Watchdog Raw Interrupt Status                                         */
  u32  MIS;                               /*!< Watchdog Masked Interrupt Status                                      */
  u32  RESERVED[256];
  u32  TEST;                              /*!< Watchdog Test                                                         */
  u32  RESERVED1[505];
  u32  LOCK;                              /*!< Watchdog Lock                                                         */
} WATCHDOG0_Type;

#define WATCHDOG0 ((WATCHDOG0_Type *)  0x40000000)

#endif