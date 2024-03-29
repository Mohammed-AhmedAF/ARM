#ifndef _PWM_PRIVATE_H
#define _PWM_PRIVATE_H

#define PWM0_CTL * ((u32*) 0x40028000)
#define PWM0_SYNC * ((u32*) 0x40028004)
#define PWM0_ENABLE * ((u32*) 0x40028008)
#define PWM0_INVERT * ((u32*) 0x4002800C)
#define PWM0_FAULT * ((u32*) 0x40028010)
#define PWM0_INTEN * ((u32*) 0x40028014)
#define PWM0_RIS * ((u32*) 0x40028018)
#define PWM0_ISC * ((u32*) 0x4002801C)
#define PWM0_STATUS * ((u32*) 0x40028020)
#define PWM0_FAULTVAL * ((u32*) 0x40028024)
#define PWM0_ENUPD * ((u32*) 0x40028028)
#define PWM0_CTL0 * ((u32*) 0x40028040)
#define PWM0_CTL1 * ((u32*) 0x40028080)
#define PWM0_CTL2 * ((u32*) 0x400280C0)
#define PWM0_CTL3 * ((u32*) 0x40028100)
#define PWM0_INTEN0 * ((u32*) 0x40028044)
#define PWM0_INTEN1 * ((u32*) 0x40028084)
#define PWM0_INTEN2 * ((u32*) 0x400280C4)
#define PWM0_INTEN3 * ((u32*) 0x40028104)
#define PWM0_RIS0 * ((u32*) 0x40028048)
#define PWM0_RIS1 * ((u32*) 0x40028088)
#define PWM0_RIS2 * ((u32*) 0x400280C8)
#define PWM0_RIS3 * ((u32 * const) 0x40028108)
#define PWM0_ISC0 * ((u32*) 0x4002804C)
#define PWM0_ISC1 * ((u32*) 0x4002808C)
#define PWM0_ISC2 * ((u32*) 0x400280CC)
#define PWM0_ISC3 * ((u32*) 0x4002810C)
#define PWM0_LOAD0 * ((u32*) 0x40028050)
#define PWM0_LOAD1 * ((u32*) 0x40028090)
#define PWM0_LOAD2 * ((u32*) 0x400280D0)
#define PWM0_LOAD3 * ((u32*) 0x40028110)
#define PWM0_COUNT0 * ((u32*) 0x40028054)
#define PWM0_COUNT1 * ((u32*) 0x40028094)
#define PWM0_COUNT2 * ((u32*) 0x400280D4)
#define PWM0_COUNT3 * ((u32*) 0x40028114)
#define PWM0_CMPA0 * ((u32*) 0x40028058)
#define PWM0_CMPA1 * ((u32*) 0x40028098)
#define PWM0_CMPA2 * ((u32*) 0x400280D8)
#define PWM0_CMPA3 * ((u32*) 0x40028118)
#define PWM0_CMPB0 * ((u32*) 0x4002805C)
#define PWM0_CMPB1 * ((u32*) 0x4002809C)
#define PWM0_CMPB2 * ((u32*) 0x400280DC)
#define PWM0_CMPB3 * ((u32*) 0x4002811C)
#define PWM0_GENA0 * ((u32*) 0x40028060)
#define PWM0_GENA1 * ((u32*) 0x400280A0)
#define PWM0_GENA2 * ((u32*) 0x400280E0)
#define PWM0_GENA3 * ((u32*) 0x40028120)
#define PWM0_GENB0 * ((u32*) 0x40028064)
#define PWM0_GENB1 * ((u32*) 0x400280A4)
#define PWM0_GENB2 * ((u32*) 0x400280E4)
#define PWM0_GENB3 * ((u32*) 0x40028124)


#endif
