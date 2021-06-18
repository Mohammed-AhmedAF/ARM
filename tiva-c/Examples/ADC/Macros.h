#ifndef _MACROS_H
#define _MACROS_H

#define SET_BIT(reg,bit) reg |= (1<<bit)
#define CLEAR_BIT(reg,bit) reg &= ~(1<<bit)
#define GET_BIT(reg,bit) ((reg>>bit)&1)
#define TOGGLE_BIT(reg,bit) reg ^= (1<<bit)
#endif
