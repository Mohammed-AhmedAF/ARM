	AREA |.text|,CODE,READONLY,ALIGN=2
	THUMB ;Informs the assembler that the following code is THUMB instructions.
	EXTERN currentPt ;Imports the symbol only if it is referred to in the current assembly file. 
	EXPORT SysTick_Handler ;EXPORT declares a symbol that can be used by the compiler to resolve a symbol reference in separate object or library files.
	EXPORT osSchedulerLaunch
		
SysTick_Handler ;saved automatically: R0,R1,R2,R3,R12,lr,pc,psr
	CPSID I ;Disable interrupts (Change Processor State Interrupt Disable)
	PUSH {R4-R11} ;Save R4,R5,R6,R7,R8,R9,R10,R11 (Registers are pushed to a full descending stack)
	LDR R0,=currentPt ;Load the TCB of thread about to be suspended (LDR Pseudo-instruction)
	LDR R1,[R0] ;R1 = currentPt 
	STR SP,[R1] ;Store the stack pointer of processor into the stack pointer of the thread to be suspended
	LDR R1,[R1,#4] ;R1 = next TCB to be switched to (pre-indixed immediate offset)
	STR R1,[R0] ;Store value of R1, next of TCB, into the address of R0 which holds currentPt
	LDR SP,[R1] ;SP is equal to the stack pointer of the new thread (switched to)
	POP {R4-R11} ;Restore the registers we pushed into the stack (Pops registers off a full-descending stack)
	CPSIE I ;Enable interrupt (Change Processor State Interrupt Enable)
	BX LR ;Return from subroutine, this will restore automatically saved registers. BX branch and exchange instruction set if required.
	
osSchedulerLaunch
	LDR R0,=currentPt
	LDR R2,[R0]
	LDR SP,[R2] ;The address in currentPt is loaded into SP
	POP {R4-R11}
	POP {R0-R3}
	POP {R12}
	ADD SP,SP,#4 ;Skip LR
	POP {LR} ; ;Create a new start location
	ADD SP,SP,#4 ;Skip PSR
	CPSIE I ;Enable global interrupt
	BX LR ;Return from subroutine
	
	
	ALIGN 
	END ;End of assembly file
	
