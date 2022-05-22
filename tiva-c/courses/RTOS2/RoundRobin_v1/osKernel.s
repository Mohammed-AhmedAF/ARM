	AREA |.text|,CODE,READONLY,ALIGN=2
	THUMB
	EXTERN currentPt
	EXPORT SysTick_Handler
	EXPORT osSchedulerLaunch
		
SysTick_Handler ;saved automatically: R0,R1,R2,R3,R12,lr,pc,psr
	CPSID I ;Disable interrupts
	PUSH {R4-R11} ;Save R4,R5,R6,R7,R8,R9,R10,R11
	LDR R0,=currentPt ;Load the TCB of thread about to be suspended
	LDR R1,[R0] ;R1 = currentPt
	STR SP,[R1] ;Store the stack pointer of processor into the stack pointer of the thread to be suspended
	LDR R1,[R1,#4] ;R1 = next TCB to be switched to (pre-indixed immediate offset)
	STR R1,[R0] ;Store value of R1, next of TCB, into the address of R0 which holds currentPt
	LDR SP,[R1] ;SP is equal to the stack pointer of the new thread (switched to)
	POP {R4-R11} ;Restore the registers we pushed into the stack
	CPSIE I ;Enable interrupt
	BX LR ;Return from subroutine, this will restore automatically saved registers
	
osSchedulerLaunch
	LDR R0,=currentPt
	LDR R2,[R0]
	LDR SP,[R2]
	POP {R4-R11}
	POP {R0-R3}
	POP {R12}
	ADD SP,SP,#4
	POP {LR}
	ADD SP,SP,#4
	CPSIE I
	BX LR
	
	
	ALIGN 
	END
	
