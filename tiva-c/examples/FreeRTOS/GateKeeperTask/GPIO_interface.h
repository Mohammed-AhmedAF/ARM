#ifndef _GPIO_INTERFACE_H
#define _GPIO_INTERFACE_H

typedef struct {
	u8 u8Port;
	u8 u8Pin;
	u8 u8Direction;
	u8 u8DigEnable;
	u8 u8PullUpRes;
	u8 u8PullDownRes;
	u8 u8AlternateFunc;
} GPIOConfig_t;

typedef struct {
	u8 u8PullResistance;
	u8 u8InterruptSense;
	u8 u8BothEdges;
	u8 u8InterruptEvent;
	void (*ptrFunc) (void);

} ExtInterruptConfig_t;


void GPIO_vidSetPinValue(u8 u8PortNumCpy,u8 u8PinNumCpy, u8 u8ValueCpy);
void GPIO_vidSetPinDirection(u8 u8PortNumCpy, u8 u8PinCpy,u8 u8DirCpy);
u8 GPIO_u8GetPinValue(u8 u8Port, u8 u8Pin);
void GPIO_vidSetPinDigEnable(u8 u8PortNumCpy, u8 u8PinCpy, u8 u8DigEnable);
void GPIO_vidTogglePin(u8 u8Port, u8 u8Pin);
void GPIO_vidConfigurePin(GPIOConfig_t * stGPIOConfig);
void GPIO_vidConfigurePUR(u8 u8Port, u8 u8Pin, u8 u8PURConfig);
void GPIO_vidConfigurePDR(u8 u8Port, u8 u8Pin, u8 u8PDRConfig);
void GPIO_vidSelectInterruptSense(u8 u8Port, u8 u8Pin, u8 u8Sense);
void GPIO_vidSelectAlterFunction(u8 u8PortNumCpy, u8 u8PinNumCpy);
void GPIO_vidConfigAnalogFunction(u8 u8Port, u8 u8Pin, u8 u8Config);
void GPIO_vidConfigurePullDown(u8 u8Port, u8 u8Pin, u8 u8PURConfig);
void GPIO_vidEnableInterrupt(u8 u8Port, u8 u8Pin);
void GPIO_vidDisableInterrupt(u8 u8Port, u8 u8Pin);
void GPIO_vidSelectInterruptEvent(u8 u8Port, u8 u8Pin, u8 u8Event);
void GPIO_vidInterruptBothEdges(u8 u8Port, u8 u8Pin, u8 u8BothEdges);
void GPIO_vidClearInterrupt(u8 u8Port, u8 u8Pin);
void GPIO_vidUnlock(u8 u8Port);
void GPIO_vidLock(u8 u8Port);
void GPIO_vidCommit(u8 u8Port,u8 u8Pin);
void GPIO_vidConfigPortControl(u8 u8Port, u8 u8Pin, u8 u8Value);
void GPIO_vidPutISR(u8 u8Port,void (*ptrF) (void));
void GPIO_vidConfigInterrupt(u8 u8Port, u8 u8Pin, ExtInterruptConfig_t * extInterruptConfig);
u8 GPIO_u8GetInterruptStatus(u8 u8Port, u8 u8Pin);



#define GPIO_PORTA 0
#define GPIO_PORTB 1
#define GPIO_PORTC 2
#define GPIO_PORTD 3
#define GPIO_PORTE 4
#define GPIO_PORTF 5

#define GPIO_PIN0 0
#define GPIO_PIN1 1
#define GPIO_PIN2 2
#define GPIO_PIN3 3
#define GPIO_PIN4 4
#define GPIO_PIN5 5
#define GPIO_PIN6 6
#define GPIO_PIN7 7

#define GPIO_LED_RED GPIO_PIN1
#define GPIO_LED_BLUE GPIO_PIN2
#define GPIO_LED_GREEN GPIO_PIN3

#define GPIO_INPUT 0
#define GPIO_OUTPUT 1

#define GPIO_DIR_INPUT 0
#define GPIO_DIR_OUTPUT 1

#define GPIO_VAL_HIGH 1
#define GPIO_VAL_LOW 0

#define GPIO_DEN_SET 1
#define GPIO_DEN_CLEAR 0

#define GPIO_ALTERFUNC_UNSET 0
#define GPIO_ALTERFUNC_SET 1

#define GPIO_ANALOG_CLEAR 0
#define GPIO_ANALOG_SET 1

#define GPIO_PUR_DISABLED 0
#define GPIO_PUR_ENABLED 1

#define GPIO_PDR_DISABLED 0
#define GPIO_PDR_ENABLED 1

#define GPIO_SENSE_EDGE 0
#define GPIO_SENSE_LEVEL 1

/*Interrupt event*/
#define GPIO_LL_FE 0
#define GPIO_HL_RE 1
#define GPIO_EVENT_FE GPIO_LL_FE
#define GPIO_EVENT_RE GPIO_HL_RE
#define GPIO_EVENT_LL GPIO_LL_FE
#define GPIO_EVENT_HL GPIO_HL_RE

#define GPIO_EVENT_FALLINGEDGE GPIO_LL_FE 
#define GPIO_EVENT_RISINGEDGE GPIO_HL_RE

/*Interrupt both edges*/
#define GPIO_INTERRUPT_EVENTCONTROLLED 0
#define GPIO_INTERRUPT_BOTHEDGES 1


#endif
