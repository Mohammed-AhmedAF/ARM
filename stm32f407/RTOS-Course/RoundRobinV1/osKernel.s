				AREA | .text|,CODE,READONLY,ALIGN=2
				THUMB
				EXTERN currentPt
				EXPORT SysTick_Handler
				EXPORT osSchedulerLaunch
					
SysTick_Handler ;Saves register r0,r1,r2,r3,r12,lr,pc,psr
	CPSID I;Disable interrupt
	PUSH {R4-R11} ;saves r4,r5,r6,r7,r8,r9,r10,r11
	LDR R0,=currentPt
	LDR R1,[R0] ;  r1 = currentPt
	STR SP,[R1]
	
	
	LDR R1,[R1,#4] ;Takes us to the second entry in the thread control block
	;R1 = currentPt->next
	STR R1,[R0]
	
	LDR SP,[R1] ; SP = currentPt->stackPt
	POP {R4-R11}
	
	CPSIE I
	BX LR
	
osSchedulerLaunch
	LDR R0,=currentPt
	LDR R2,[R0] ;R2=currentPt
	LDR SP,[R2] ;SP = currentPt->stackPt
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