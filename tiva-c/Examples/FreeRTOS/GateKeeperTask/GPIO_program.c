/*
 * Author: Mohamed Ahmed Abd Al-Fattah
 * Purpose: GPIO driver for Tiva-C
 * Date: 16-10-2018
 *
 */

#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_config.h"
#include "GPIO_private.h"
#include "GPIO_interface.h"

static void (*ptrF_GPIOA) (void);
static void (*ptrF_GPIOB) (void);
static void (*ptrF_GPIOC) (void);
static void (*ptrF_GPIOD) (void);
static void (*ptrF_GPIOE) (void);
static void (*ptrF_GPIOF) (void);

void GPIO_vidSetPinDirection(u8 u8PortNumCpy, u8 u8PinNumCpy, u8 u8DirectionCpy) {
	switch (u8PortNumCpy) {
		case GPIO_PORTA:
			if (u8DirectionCpy == GPIO_OUTPUT) {
				SET_BIT(GPIOA_DIR,u8PinNumCpy);	
			}
			else {
				CLEAR_BIT(GPIOA_DIR,u8PinNumCpy);
			}
			break;
		case GPIO_PORTB:
			if (u8DirectionCpy == GPIO_OUTPUT) {
				SET_BIT(GPIOB_DIR,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOB_DIR,u8PinNumCpy);	
			}
			break;
		case GPIO_PORTC:
			if (u8DirectionCpy == GPIO_OUTPUT) {
				SET_BIT(GPIOC_DIR,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOC_DIR,u8PinNumCpy);
			}
			break;
		case GPIO_PORTD:
			if (u8DirectionCpy == GPIO_OUTPUT) {
				SET_BIT(GPIOD_DIR,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOD_DIR,u8PinNumCpy);
			}
			break;
		case GPIO_PORTE:
			if (u8DirectionCpy == GPIO_OUTPUT)
			{
				SET_BIT(GPIOE_DIR,u8PinNumCpy);
			}
			else
			{
				CLEAR_BIT(GPIOE_DIR,u8PinNumCpy);
			}
			break;
		case GPIO_PORTF:
			if (u8DirectionCpy == GPIO_OUTPUT) {
				SET_BIT(GPIOF_DIR,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOF_DIR,u8PinNumCpy);
			}
			break;
	}

}

void GPIO_vidSetPinValue(u8 u8PortNumCpy, u8 u8PinNumCpy, u8 u8Value) {
	switch (u8PortNumCpy) {
		case GPIO_PORTA:
			if (u8Value == STD_HIGH) {
				SET_BIT(GPIOA_DATA,u8PinNumCpy);	
			}
			else {
				CLEAR_BIT(GPIOA_DATA,u8PinNumCpy);
			}
			break;
		case GPIO_PORTB:
			if (u8Value == STD_HIGH) {
				SET_BIT(GPIOB_DATA,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOB_DATA,u8PinNumCpy);	
			}
			break;
		case GPIO_PORTC:
			if (u8Value == STD_HIGH) {
				SET_BIT(GPIOC_DATA,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOC_DATA,u8PinNumCpy);
			}
			break;
		case GPIO_PORTD:
			if (u8Value == STD_HIGH) {
				SET_BIT(GPIOD_DATA,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOD_DATA,u8PinNumCpy);
			}
			break;
		case GPIO_PORTE:
			if (u8Value == STD_HIGH) {
				SET_BIT(GPIOE_DATA,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOE_DATA,u8PinNumCpy);
			}
			break;
		case GPIO_PORTF:
			if (u8Value == STD_HIGH) {
				SET_BIT(GPIOF_DATA,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOF_DATA,u8PinNumCpy);
			}
			break;
	}
}

u8 GPIO_u8GetPinValue(u8 u8Port, u8 u8Pin)
{
	switch(u8Port)
	{
		case GPIO_PORTA:
			return GET_BIT(GPIOA_DATA,u8Pin);
			break;
		case GPIO_PORTB:
			return GET_BIT(GPIOB_DATA,u8Pin);
			break;
		case GPIO_PORTC:
			return GET_BIT(GPIOC_DATA,u8Pin);
			break;
		case GPIO_PORTD:
			return GET_BIT(GPIOD_DATA,u8Pin);
			break;
		case GPIO_PORTE:
			return GET_BIT(GPIOE_DATA,u8Pin);
			break;
		case GPIO_PORTF:
			return GET_BIT(GPIOF_DATA,u8Pin);
			break;
	}
}

void GPIO_vidSetPinDigEnable(u8 u8PortNumCpy, u8 u8PinNumCpy, u8 u8DigEnable) {
	switch (u8PortNumCpy) {
		case GPIO_PORTA:
			if (u8DigEnable == GPIO_DEN_SET) {
				SET_BIT(GPIOA_DEN,u8PinNumCpy);	
			}
			else {
				CLEAR_BIT(GPIOA_DEN,u8PinNumCpy);
			}
			break;
		case GPIO_PORTB:
			if (u8DigEnable == GPIO_DEN_SET) {
				SET_BIT(GPIOB_DEN,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOB_DEN,u8PinNumCpy);	
			}
			break;
		case GPIO_PORTC:
			if (u8DigEnable == GPIO_DEN_SET) {
				SET_BIT(GPIOC_DEN,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOC_DEN,u8PinNumCpy);
			}
			break;
		case GPIO_PORTD:
			if (u8DigEnable == GPIO_DEN_SET) {
				SET_BIT(GPIOD_DEN,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOD_DEN,u8PinNumCpy);
			}
			break;
		case GPIO_PORTE:
			if (u8DigEnable == GPIO_DEN_SET) {
				SET_BIT(GPIOE_DEN,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOE_DEN,u8PinNumCpy);
			}
			break;
		case GPIO_PORTF:
			if (u8DigEnable == GPIO_DEN_SET) {
				SET_BIT(GPIOF_DEN,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOF_DEN,u8PinNumCpy);
			}
			break;
	}
}

void GPIO_vidConfigurePin(GPIOConfig_t * stGPIOConfig)
{
	/*Digital pin enable*/
	GPIO_vidSetPinDigEnable(stGPIOConfig->u8Port,stGPIOConfig->u8Pin,stGPIOConfig->u8DigEnable);
	
	/*Direction*/
	GPIO_vidSetPinDirection(stGPIOConfig->u8Port,stGPIOConfig->u8Pin,stGPIOConfig->u8Direction);
	
	/*Alternate function setting*/
	if (stGPIOConfig->u8AlternateFunc == GPIO_ALTERFUNC_SET)
	{
		GPIO_vidSelectAlterFunction(stGPIOConfig->u8Port,stGPIOConfig->u8Pin);
	}
	else
	{
	
	}
	
	/*Pull-up Resistance*/
	GPIO_vidConfigurePUR(stGPIOConfig->u8Port,stGPIOConfig->u8Pin,stGPIOConfig->u8PullUpRes);
	
	/*Pull-down Resistance*/
	GPIO_vidConfigurePDR(stGPIOConfig->u8Port,stGPIOConfig->u8Pin,stGPIOConfig->u8PullDownRes);

	
}

void GPIO_vidTogglePin(u8 u8Port, u8 u8Pin)
{
	switch(u8Port)
	{
		case GPIO_PORTA:
			TOGGLE_BIT(GPIOA_DATA,u8Pin);
		break;
		case GPIO_PORTB:
			TOGGLE_BIT(GPIOB_DATA,u8Pin);
		break;
		case GPIO_PORTC:
			TOGGLE_BIT(GPIOC_DATA,u8Pin);
		break;
		case GPIO_PORTD:
			TOGGLE_BIT(GPIOD_DATA,u8Pin);
			break;
		case GPIO_PORTE:
			TOGGLE_BIT(GPIOE_DATA,u8Pin);
			break;
		case GPIO_PORTF:
			TOGGLE_BIT(GPIOF_DATA,u8Pin);
			break;
	}
}

void GPIO_vidConfigurePUR(u8 u8Port, u8 u8Pin, u8 u8PURConfig)
{
switch (u8Port) {
		case GPIO_PORTA:
			if (u8PURConfig == GPIO_PUR_ENABLED) {
				SET_BIT(GPIOA_PUR,u8Pin);	
			}
			else {
				CLEAR_BIT(GPIOA_PUR,u8Pin);
			}
			break;
		case GPIO_PORTB:
			if (u8PURConfig == GPIO_PUR_ENABLED) {
				SET_BIT(GPIOB_PUR,u8Pin);
			}
			else {
				CLEAR_BIT(GPIOB_PUR,u8Pin);	
			}
			break;
		case GPIO_PORTC:
			if (u8PURConfig == GPIO_PUR_ENABLED) {
				SET_BIT(GPIOC_PUR,u8Pin);
			}
			else {
				CLEAR_BIT(GPIOC_PUR,u8Pin);
			}
			break;
		case GPIO_PORTD:
			if (u8PURConfig == GPIO_PUR_ENABLED) {
				SET_BIT(GPIOD_PUR,u8Pin);
			}
			else {
				CLEAR_BIT(GPIOD_PUR,u8Pin);
			}
			break;
		case GPIO_PORTE:
			if (u8PURConfig == GPIO_PUR_ENABLED) {
				SET_BIT(GPIOE_PUR,u8Pin);
			}
			else {
				CLEAR_BIT(GPIOE_PUR,u8Pin);
			}
			break;
		case GPIO_PORTF:
			if (u8PURConfig == GPIO_PUR_ENABLED) {
				SET_BIT(GPIOF_PUR,u8Pin);
			}
			else {
				CLEAR_BIT(GPIOF_PUR,u8Pin);
			}
			break;
	}
}

void GPIO_vidConfigurePDR(u8 u8Port, u8 u8Pin, u8 u8PDRConfig)
{
switch (u8Port) {
		case GPIO_PORTA:
			if (u8PDRConfig == GPIO_PDR_ENABLED) {
				SET_BIT(GPIOA_PDR,u8Pin);	
			}
			else {
				CLEAR_BIT(GPIOA_PDR,u8Pin);
			}
			break;
		case GPIO_PORTB:
			if (u8PDRConfig == GPIO_PUR_ENABLED) {
				SET_BIT(GPIOB_PDR,u8Pin);
			}
			else {
				CLEAR_BIT(GPIOB_PDR,u8Pin);	
			}
			break;
		case GPIO_PORTC:
			if (u8PDRConfig == GPIO_PUR_ENABLED) {
				SET_BIT(GPIOC_PDR,u8Pin);
			}
			else {
				CLEAR_BIT(GPIOC_PDR,u8Pin);
			}
			break;
		case GPIO_PORTD:
			if (u8PDRConfig == GPIO_PUR_ENABLED) {
				SET_BIT(GPIOD_PDR,u8Pin);
			}
			else {
				CLEAR_BIT(GPIOD_PDR,u8Pin);
			}
			break;
		case GPIO_PORTE:
			if (u8PDRConfig == GPIO_PDR_ENABLED) {
				SET_BIT(GPIOE_PDR,u8Pin);
			}
			else {
				CLEAR_BIT(GPIOE_PDR,u8Pin);
			}
			break;
		case GPIO_PORTF:
			if (u8PDRConfig == GPIO_PDR_ENABLED) {
				SET_BIT(GPIOF_PDR,u8Pin);
			}
			else {
				CLEAR_BIT(GPIOF_PDR,u8Pin);
			}
			break;
	}
}

void GPIO_vidConfigurePullDown(u8 u8Port, u8 u8Pin, u8 u8PURConfig)
{
switch (u8Port) {
		case GPIO_PORTA:
			if (u8PURConfig == GPIO_PDR_ENABLED) {
				SET_BIT(GPIOA_PDR,u8Pin);	
			}
			else {
				CLEAR_BIT(GPIOA_PDR,u8Pin);
			}
			break;
		case GPIO_PORTB:
			if (u8PURConfig == GPIO_PDR_ENABLED) {
				SET_BIT(GPIOB_PDR,u8Pin);
			}
			else {
				CLEAR_BIT(GPIOB_PDR,u8Pin);	
			}
			break;
		case GPIO_PORTC:
			if (u8PURConfig == GPIO_PDR_ENABLED) {
				SET_BIT(GPIOC_PDR,u8Pin);
			}
			else {
				CLEAR_BIT(GPIOC_PDR,u8Pin);
			}
			break;
		case GPIO_PORTD:
			if (u8PURConfig == GPIO_PDR_ENABLED) {
				SET_BIT(GPIOD_PDR,u8Pin);
			}
			else {
				CLEAR_BIT(GPIOD_PDR,u8Pin);
			}
			break;
		case GPIO_PORTE:
			if (u8PURConfig == GPIO_PDR_ENABLED) {
				SET_BIT(GPIOE_PDR,u8Pin);
			}
			else {
				CLEAR_BIT(GPIOE_PDR,u8Pin);
			}
			break;
		case GPIO_PORTF:
			if (u8PURConfig == GPIO_PDR_ENABLED) {
				SET_BIT(GPIOF_PDR,u8Pin);
			}
			else {
				CLEAR_BIT(GPIOF_PDR,u8Pin);
			}
			break;
	}
}

void GPIO_vidSelectInterruptSense(u8 u8Port, u8 u8Pin, u8 u8Sense)
{
	switch (u8Port)
	{
		case GPIO_PORTA:
			if (u8Sense == GPIO_SENSE_EDGE)
			{
				CLEAR_BIT(GPIOA_IS,u8Pin);
			}
			else
			{
				SET_BIT(GPIOA_IS,u8Pin);
			}
			break;
			case GPIO_PORTB:
			if (u8Sense == GPIO_SENSE_EDGE)
			{
				CLEAR_BIT(GPIOB_IS,u8Pin);
			}
			else
			{
				SET_BIT(GPIOB_IS,u8Pin);
			}
			break;
		case GPIO_PORTC:
			if (u8Sense == GPIO_SENSE_EDGE)
			{
				CLEAR_BIT(GPIOC_IS,u8Pin);
			}
			else
			{
				SET_BIT(GPIOC_IS,u8Pin);
			}
			break;
		case GPIO_PORTD:
			if (u8Sense == GPIO_SENSE_EDGE)
			{
				CLEAR_BIT(GPIOD_IS,u8Pin);
			}
			else
			{
				SET_BIT(GPIOD_IS,u8Pin);
			}
			break;
		case GPIO_PORTE:
			if (u8Sense == GPIO_SENSE_EDGE)
			{
				CLEAR_BIT(GPIOE_IS,u8Pin);
			}
			else
			{
				SET_BIT(GPIOE_IS,u8Pin);
			}
			break;
		case GPIO_PORTF:
			if (u8Sense == GPIO_SENSE_EDGE)
			{
				CLEAR_BIT(GPIOF_IS,u8Pin);
			}
			else
			{
				SET_BIT(GPIOF_IS,u8Pin);
			}
			break;
	}

}

/*To select alternate function for pin*/
void GPIO_vidSelectAlterFunction(u8 u8PortNumCpy, u8 u8PinNumCpy) {
	switch(u8PortNumCpy) {
		case GPIO_PORTA:
			SET_BIT(GPIOA_AFSEL,u8PinNumCpy);
			break;
		case GPIO_PORTB:
			SET_BIT(GPIOB_AFSEL,u8PinNumCpy);
			break;
		case GPIO_PORTC:
			SET_BIT(GPIOC_AFSEL,u8PinNumCpy);
			break;
		case GPIO_PORTD:
			SET_BIT(GPIOD_AFSEL,u8PinNumCpy);
			break;
		case GPIO_PORTE:
			SET_BIT(GPIOE_AFSEL,u8PinNumCpy);
			break;
		case GPIO_PORTF:
			SET_BIT(GPIOF_AFSEL,u8PinNumCpy);
			break;
	}
}

void GPIO_vidEnableInterrupt(u8 u8Port, u8 u8Pin)
{
switch(u8Port) {
		case GPIO_PORTA:
			SET_BIT(GPIOA_IM,u8Pin);
			break;
		case GPIO_PORTB:
			SET_BIT(GPIOB_IM,u8Pin);
			break;
		case GPIO_PORTC:
			SET_BIT(GPIOC_IM,u8Pin);
			break;
		case GPIO_PORTD:
			SET_BIT(GPIOD_IM,u8Pin);
			break;
		case GPIO_PORTE:
			SET_BIT(GPIOE_IM,u8Pin);
			break;
		case GPIO_PORTF:
			SET_BIT(GPIOF_IM,u8Pin);
			break;
	}
}

void GPIO_vidDisableInterrupt(u8 u8Port, u8 u8Pin)
{
switch(u8Port) {
		case GPIO_PORTA:
			CLEAR_BIT(GPIOA_IM,u8Pin);
			break;
		case GPIO_PORTB:
			CLEAR_BIT(GPIOB_IM,u8Pin);
			break;
		case GPIO_PORTC:
			CLEAR_BIT(GPIOC_IM,u8Pin);
			break;
		case GPIO_PORTD:
			CLEAR_BIT(GPIOD_IM,u8Pin);
			break;
		case GPIO_PORTE:
			CLEAR_BIT(GPIOE_IM,u8Pin);
			break;
		case GPIO_PORTF:
			CLEAR_BIT(GPIOF_IM,u8Pin);
			break;
	}
}

void GPIO_vidSelectInterruptEvent(u8 u8Port, u8 u8Pin, u8 u8Event)
{
	switch(u8Port)
	{
		case GPIO_PORTA:
			if (u8Event == GPIO_HL_RE)
			{
				SET_BIT(GPIOA_IEV,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOA_IEV,u8Pin);
			}
			break;
		case GPIO_PORTB:
			if (u8Event == GPIO_HL_RE)
			{
				SET_BIT(GPIOB_IEV,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOB_IEV,u8Pin);
			}
			break;
		case GPIO_PORTC:
			if (u8Event == GPIO_HL_RE)
			{
				SET_BIT(GPIOC_IEV,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOC_IEV,u8Pin);
			}
			break;
		case GPIO_PORTD:
			if (u8Event == GPIO_HL_RE)
			{
				SET_BIT(GPIOD_IEV,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOD_IEV,u8Pin);
			}
			break;
		case GPIO_PORTE:
			if (u8Event == GPIO_HL_RE)
			{
				SET_BIT(GPIOE_IEV,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOE_IEV,u8Pin);
			}
			break;
		case GPIO_PORTF:
			if (u8Event == GPIO_HL_RE)
			{
				SET_BIT(GPIOF_IEV,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOF_IEV,u8Pin);
			}
			break;
	}
}

void GPIO_vidInterruptBothEdges(u8 u8Port, u8 u8Pin, u8 u8BothEdges)
{
	switch(u8Port)
	{
		case GPIO_PORTA:
			if (u8BothEdges == GPIO_INTERRUPT_BOTHEDGES)
			{
				SET_BIT(GPIOA_IBE,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOA_IBE,u8Pin);
			}
			break;
		case GPIO_PORTB:
			if (u8BothEdges == GPIO_INTERRUPT_BOTHEDGES)
			{
				SET_BIT(GPIOB_IBE,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOB_IBE,u8Pin);
			}
			break;
		case GPIO_PORTC:
			if (u8BothEdges == GPIO_INTERRUPT_BOTHEDGES)
			{
				SET_BIT(GPIOC_IBE,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOC_IBE,u8Pin);
			}
			break;
		case GPIO_PORTD:
			if (u8BothEdges == GPIO_INTERRUPT_BOTHEDGES)
			{
				SET_BIT(GPIOD_IBE,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOD_IBE,u8Pin);
			}
			break;
		case GPIO_PORTE:
			if (u8BothEdges == GPIO_INTERRUPT_BOTHEDGES)
			{
				SET_BIT(GPIOE_IBE,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOE_IBE,u8Pin);
			}
			break;
		case GPIO_PORTF:
			if (u8BothEdges == GPIO_INTERRUPT_BOTHEDGES)
			{
				SET_BIT(GPIOF_IBE,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOF_IBE,u8Pin);
			}
			break;
	}
}

void GPIO_vidClearInterrupt(u8 u8Port, u8 u8Pin)
{
	switch(u8Port)
	{
		case GPIO_PORTA:
			SET_BIT(GPIOA_ICR,u8Pin);
			break;
		case GPIO_PORTB:
			SET_BIT(GPIOB_ICR,u8Pin);
			break;
		case GPIO_PORTC:
			SET_BIT(GPIOC_ICR,u8Pin);
			break;
		case GPIO_PORTD:
			SET_BIT(GPIOD_ICR,u8Pin);
			break;
		case GPIO_PORTE:
			SET_BIT(GPIOE_ICR,u8Pin);
			break;
		case GPIO_PORTF:
			SET_BIT(GPIOF_ICR,u8Pin);
			break;
	}
}

void GPIO_vidUnlock(u8 u8Port)
{
	switch(u8Port)
	{
		case GPIO_PORTA:
				GPIOA_LOCK = 0x4C4F434B;
			break;
		case GPIO_PORTB:
				GPIOB_LOCK = 0x4C4F434B;
			break;
		case GPIO_PORTC:
				GPIOC_LOCK = 0x4C4F434B;
			break;
		case GPIO_PORTD:
				GPIOD_LOCK = 0x4C4F434B;
			break;
		case GPIO_PORTE:
				GPIOE_LOCK = 0x4C4F434B;
			break;
		case GPIO_PORTF:
				GPIOF_LOCK = 0x4C4F434B;
			break;
	}
}

void GPIO_vidLock(u8 u8Port)
{
	switch(u8Port)
	{
		case GPIO_PORTA:
			GPIOA_LOCK = 0;
			break;
		case GPIO_PORTB:
			GPIOB_LOCK = 0;
			break;
		case GPIO_PORTC:
			GPIOC_LOCK = 0;
			break;
		case GPIO_PORTD:
			GPIOD_LOCK = 0;
			break;
		case GPIO_PORTE:
			GPIOE_LOCK = 0;
			break;
		case GPIO_PORTF:
			GPIOF_LOCK = 0;
			break;
	}
}

void GPIO_vidCommit(u8 u8Port,u8 u8Pin)
{
	switch(u8Port)
	{
		case GPIO_PORTA:
			SET_BIT(GPIOA_CR,u8Pin);
			break;
		case GPIO_PORTB:
			SET_BIT(GPIOB_CR,u8Pin);
			break;
		case GPIO_PORTC:
			SET_BIT(GPIOC_CR,u8Pin);
			break;
		case GPIO_PORTD:
			SET_BIT(GPIOD_CR,u8Pin);
			break;
		case GPIO_PORTE:
			SET_BIT(GPIOE_CR,u8Pin);
			break;
		case GPIO_PORTF:
			SET_BIT(GPIOF_CR,u8Pin);
			break;
	}
}

void GPIO_vidConfigAnalogFunction(u8 u8Port, u8 u8Pin, u8 u8Config)
{
	switch(u8Port)
	{
		case GPIO_PORTA:
			if (u8Config == GPIO_ANALOG_SET)
			{
				SET_BIT(GPIOA_AMSEL,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOA_AMSEL,u8Pin);
			}
			break;
		case GPIO_PORTB:
			if (u8Config == GPIO_ANALOG_SET)
			{
				SET_BIT(GPIOB_AMSEL,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOB_AMSEL,u8Pin);
			}
			break;
		case GPIO_PORTC:
			if (u8Config == GPIO_ANALOG_SET)
			{
				SET_BIT(GPIOC_AMSEL,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOC_AMSEL,u8Pin);
			}
			break;
		case GPIO_PORTD:
			if (u8Config == GPIO_ANALOG_SET)
			{
				SET_BIT(GPIOD_AMSEL,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOD_AMSEL,u8Pin);
			}
			break;
		case GPIO_PORTE:
			if (u8Config == GPIO_ANALOG_SET)
			{
				SET_BIT(GPIOE_AMSEL,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOE_AMSEL,u8Pin);
			}
			break;
		case GPIO_PORTF:
			if (u8Config == GPIO_ANALOG_SET)
			{
				SET_BIT(GPIOF_AMSEL,u8Pin);
			}
			else
			{
				CLEAR_BIT(GPIOF_AMSEL,u8Pin);
			}
			break;
	}
}

void GPIO_vidConfigPortControl(u8 u8Port, u8 u8Pin, u8 u8Value)
{
	switch(u8Port)
	{
		case GPIO_PORTA:
			GPIOA_PCTL |= (u8Value<<(4*u8Pin));
		break;
		case GPIO_PORTB:
			GPIOB_PCTL |= (u8Value<<(4*u8Pin));
			break;
		case GPIO_PORTC:
			GPIOC_PCTL |= (u8Value<<(4*u8Pin));
			break;
		case GPIO_PORTD:
			GPIOD_PCTL |= (u8Value<<(4*u8Pin));
			break;
		case GPIO_PORTE:
			GPIOE_PCTL |= (u8Value<<(4*u8Pin));
			break;
		case GPIO_PORTF:
			GPIOF_PCTL |= (u8Value<<(4*u8Pin));
			break;
	}
}

void GPIO_vidPutISR(u8 u8Port, void (*ptrF) (void))
{
	switch(u8Port)
	{
		case GPIO_PORTA:
			ptrF_GPIOA = ptrF;
			break;
		case GPIO_PORTB:
			ptrF_GPIOB = ptrF;
			break;
		case GPIO_PORTC:
			ptrF_GPIOC = ptrF;
		break;
		case GPIO_PORTD:
			ptrF_GPIOD = ptrF;
		break;
		case GPIO_PORTE:
			ptrF_GPIOE = ptrF;
		break;
		case GPIO_PORTF:
			ptrF_GPIOF = ptrF;
		break;
	}

}


void GPIO_vidConfigInterrupt(u8 u8Port, u8 u8Pin,ExtInterruptConfig_t * extInterruptConfig)
{
	/*Pull resistance*/
	GPIO_vidConfigurePUR(u8Port,u8Pin,extInterruptConfig->u8PullResistance);

	/*Event Sense*/
	GPIO_vidSelectInterruptSense(u8Port,u8Pin,extInterruptConfig->u8InterruptSense);

	/*Both edges*/
	GPIO_vidInterruptBothEdges(u8Port,u8Pin,extInterruptConfig->u8BothEdges);

	/*Interrupt event*/
	GPIO_vidSelectInterruptEvent(u8Port,u8Pin,extInterruptConfig->u8InterruptEvent);

	/*ISR function*/
	GPIO_vidPutISR(u8Port,extInterruptConfig->ptrFunc);
	
	/*Clear interrupt*/
	GPIO_vidClearInterrupt(u8Port,u8Pin);

	/*Enable interrupt*/
	GPIO_vidEnableInterrupt(u8Port,u8Pin);

}

u8 GPIO_u8GetInterruptStatus(u8 u8Port, u8 u8Pin)
{
	u8 result = 0;
	switch(u8Port)
	{
		case GPIO_PORTA:
			result = GET_BIT(GPIOA_MIS,u8Pin);
			break;
		case GPIO_PORTB:
			result = GET_BIT(GPIOB_MIS,u8Pin);
		break;
		case GPIO_PORTC:
			result = GET_BIT(GPIOC_MIS,u8Pin);
			break;
		case GPIO_PORTD:
			result = GET_BIT(GPIOD_MIS,u8Pin);
			break;
		case GPIO_PORTE:
			result = GET_BIT(GPIOE_MIS,u8Pin);
			break;
		case GPIO_PORTF:
			result = GET_BIT(GPIOF_MIS,u8Pin);
			break;
	}
	return result;
}

void GPIOA_Handler()
{
	ptrF_GPIOA();
}

void GPIOB_Handler()
{
	ptrF_GPIOB();
}

void GPIOC_Handler()
{
	ptrF_GPIOC();
}

void GPIOD_Handler()
{
	ptrF_GPIOD();
}

void GPIOE_Handler()
{
	ptrF_GPIOE();
}
void GPIOF_Handler()
{
	ptrF_GPIOF();
}
