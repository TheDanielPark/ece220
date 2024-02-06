;Name: Daniel Park
;NETID: danielp7
;Date: 9/16/2019
;Course: ECE 220 MP2
;The goal of the project was to create a stack calculator using postfix expressions. I approached this project first
;by creating all of the subroutines. The addition and subtraction were very basic but mult and div took a little more 
;thinking. The Exponent subroutine is more complex but I realize now that I could have called on the mult subroutine.
;As I was working, I forgot about the exception cases e.g. dividing by zero or exponents that are 0. After making
;the exception code, I worked on evaluate. I used the keyboard reading code from lecture and my evaluate was a 
;different approach. To print the hex value in the end, I just used my lab1 code. 
;Partners: jayhp2
;Registers are used in various different ways for each subroutine.
;


.ORIG x3000
	
;your code goes here
;R0 holds the character
;R1 holds the DSR
START
POLL1
	LDI R0, KBSR
	BRzp POLL1
	LDI R0, KBDR
POLL2
	LDI R1, DSR
	BRzp POLL2
	STI R0, DDR		;Read and echo the input
	JSR EVALUATE	;Go to evaluate
	BR DONE

ERROR
	LEA R0, INVALID
	PUTS
	BR DONE			;If there is an error, print string "Invalid Expression"


DONE
	HALT


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal

;R0 is the register that will hold the value in R3 to print
;R1 is the counter to count to 4 for each bit
;R2 Temp storage register
;R3 is the register that holds the inital hex input
;R4 Big loop counter
PRINT_HEX

		ADD R3,R0,#0
		AND R0,R0,#0
	 	AND R2,R2,#0 ;Clear R2
		AND R4,R4,#0 ;Clear R4
		ADD R4,R4,#4 ;Set R4 to 4
BLOOP   ADD R4,R4,#-1 ;Bigger loop start to decrement the counter for 4 hex symbols
		BRn DONE	 ;if the big counter loops 4 times it should stop
		AND R1,R1,#0 ;clear R1
    	ADD R1,R1,#4 ;Add 4 to R1 to set the smaller loop counter
LOOP  				 ;start of small loop
		ADD R0,R0,R0 ;left shift R0
   	    ADD R3,R3,#0 ;add 0  to get the branch option
  	    BRzp POS  	 ;if R3 has a zero in the front go to the pos loop
  	    ADD R0,R0,#1 ;add a 1 to R0 if R3 has a 1 in front
    	ADD R3,R3,R3 ;left shift R3
   	    ADD R1,R1,#-1 ;decrement R1
   	    BRp LOOP	 ;if R1 hasn't decremented 4 times loop again
   	    BRnz PRINT   ;if R1 has then print
POS   	ADD R3,R3,R3 ;Left shift R3
      	ADD R1,R1,#-1 ;decrement R1
     	BRp LOOP	 ;if R1 hasn't decremented 4 times loop again
PRINT	AND R1,R1,#0 	
		ADD R1,R0,#-10 ;Check if R0 is a hex number
		BRn NUM		 ;branch to number if it is
LETTER	ADD R0,R0,#8 
	 	ADD R0,R0,#8
	 	ADD R0,R0,#8
	 	ADD R0,R0,#8
	 	ADD R0,R0,#8
	 	ADD R0,R0,#8
	 	ADD R0,R0,#7 ;Add 55 to the register to print the hex value
		OUT			 ;print the hex value
		AND R0,R0,#0 ;clear R0
		BR  BLOOP    ;Always go back to big loop
NUM	  	ADD R0,R0,#8
	 	ADD R0,R0,#8
	 	ADD R0,R0,#8
		ADD R0,R0,#8
		ADD R0,R0,#8
		ADD R0,R0,#8 ;Add 48 to the R0 value
	  	OUT			 ;print the proper hex number
		AND R0,R0,#0 ;Clear R0
		BR  BLOOP    ;Always loop to big loop

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here
;R0 holds the input hex value
;R2 Checks to see what ascii value R0 is
;R3 is an input value
;R4 is the second input value
;R5 checks for overflow/underflow
;R6 is a temp register
LESSNUMCHECK
	ADD R2,R0,#-16
	ADD R2,R2,#-16
	ADD R2,R2,#-16	;Subtract 48 to see if the value in R0 is less than '0'
	BRn LESSNUM		;If R0 is less than '0' go to lessnum
BIGNUMCHECK
	ADD R2,R0,#-16
	ADD R2,R2,#-16
	ADD R2,R2,#-16
	ADD R2,R2,#-9	;Subtract 57 to see if the value in R0 is greater than '9'
	BRp BIGNUM
	ADD R2,R0,#-16
	ADD R2,R2,#-16
	ADD R2,R2,#-16	;Subtract 48 to store the hex value of the ascii into the base.
	ADD R0,R2,#0	;Store the hex value into R0 before pushing
	JSR PUSH		;If R0 is greater than 47 and less than 58, it is a number
	ADD R5,R5,#0
	BRp ERROR
	BR  START

LESSNUM
	ADD R6,R0,#-16
	ADD R6,R6,#-16	;Subtract 32 from the input to see if it is a space
	BRz START
	ADD R6,R6,#-10	;Subtract 42 from the input to see if it is a '*'
	BRz MULTIPLY
	ADD R6,R6,#-1	;Subtract 43 from the input to see if it is a '+'
	BRz ADDITION
	ADD R6,R6,#-2	;Subtract 45 from the input to see if it is a '-'
	BRz MINUS
	ADD R6,R6,#-2	;Subtract 47 from the input to see if it is a '/'
	BRz DIVIDE
	BR ERROR		;If it is none of these, it is invalid

BIGNUM
	ADD R2,R0,#-16
	ADD R2,R2,#-16
	ADD R2,R2,#-16
	ADD R2,R2,#-13	;Subtract 61 from inputted value to see if it is "="
	BRz EQUALSIGN
	ADD R2,R2,#-16
	ADD R2,R2,#-16
	ADD R2,R2,#-1 	;Subtract 94 from inputted value to see if it is "^"
	BRz POWER
	BR  ERROR		;If it is greater that 57 and neither "=" or "^" then send error

ADDITION
	JSR POP			;Pop a value
	ADD R5,R5,#0
	BRp ERROR		;Check if R5 is 1, if it is then error
	ADD R4,R0,#0	;Pop a value and put it into R4
	JSR POP
	ADD R5,R5,#0
	BRp ERROR		;Check if R5 is 1, if it is then error
	ADD R3,R0,#0	;Pop a value and put it into R3
	JSR PLUS		;Do the PLUS Subroutine
	JSR PUSH		;Push answer into the stack
	ADD R5,R5,#0	;Check for overflow
	BRp ERROR		;If overflow, error
	BR  START		;Go back to input reading

MINUS
	JSR POP			;Pop a value
	ADD R5,R5,#0
	BRp ERROR		;Check if R5 is 1, if it is then error
	ADD R4,R0,#0	;Pop a value and put it into R4
	JSR POP
	ADD R5,R5,#0
	BRp ERROR		;Check if R5 is 1, if it is then error
	ADD R3,R0,#0	;Pop a value and put it into R3
	JSR MIN			;Do the MIN Subroutine
	JSR PUSH		;Push answer into the stack
	ADD R5,R5,#0	;Check for overflow
	BRp ERROR		;If overflow, error
	BR  START		;Go back to input reading

MULTIPLY
	JSR POP			;Pop a value
	ADD R5,R5,#0
	BRp ERROR		;Check if R5 is 1, if it is then error
	ADD R4,R0,#0	;Pop a value and put it into R4
	JSR POP
	ADD R5,R5,#0
	BRp ERROR		;Check if R5 is 1, if it is then error
	ADD R3,R0,#0	;Pop a value and put it into R3
	JSR MUL			;Do the MUL Subroutine
	JSR PUSH		;Push answer into the stack
	ADD R5,R5,#0	;Check for overflow
	BRp ERROR		;If overflow, error
	BR  START		;Go back to input reading

DIVIDE
	JSR POP			;Pop a value
	ADD R5,R5,#0
	BRp ERROR		;Check if R5 is 1, if it is then error
	ADD R4,R0,#0	;Pop a value and put it into R4
	JSR POP
	ADD R5,R5,#0
	BRp ERROR		;Check if R5 is 1, if it is then error
	ADD R3,R0,#0	;Pop a value and put it into R3
	JSR DIV			;Do the DIV Subroutine
	JSR PUSH		;Push answer into the stack
	ADD R5,R5,#0	;Check for overflow
	BRp ERROR		;If overflow, error
	BR  START		;Go back to input reading

POWER
	JSR POP			;Pop a value
	ADD R5,R5,#0
	BRp ERROR		;Check if R5 is 1, if it is then error
	ADD R4,R0,#0	;Pop a value and put it into R4
	JSR POP
	ADD R5,R5,#0
	BRp ERROR		;Check if R5 is 1, if it is then error
	ADD R3,R0,#0	;Pop a value and put it into R3
	JSR EXP			;Do the EXP Subroutine
	JSR PUSH		;Push answer into the stack
	ADD R5,R5,#0	;Check for overflow
	BRp ERROR		;If overflow, error
	BR  START		;Go back to input reading

EQUALSIGN
	LD R3, STACK_START	;Load x4000 into R3
	LD R4, STACK_TOP	;Load whatever hex is in stack top into R4
	NOT R4,R4
	ADD R4,R4,#1		;Make R4 negative
	ADD R6,R3,R4		;Do STACK_START - STACK_TOP
	ADD R6,R6,#-1		;Add -1 to R6 
	BRnp ERROR			;If STACK_START - STACK_TOP != 0, ERROR because more than 1 value in stack
	JSR POP
	ADD R5,R5,#0		;Add 0 to R5 to get condition codes
	BRp ERROR			;If R5 is 1, error
	ADD R5,R0,#0		;If there is only 1 value in stack, put it into R5
	JSR PRINT_HEX
	BR DONE				;Branch to done once the final value is stored into R5


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

PLUS	
;your code goes here
	ADD R0,R3,R4	;Basic addition stored into R0
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
;R2 is a temp register
	AND R2,R2,#0
	NOT R2,R4
	ADD R2,R2,#1
	ADD R0,R2,R3	;Do R3-R4 and store into R0
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
	ST R3, MULTSaveR3	;Store R3 into memory
	AND R0,R0,#0
	ADD R3,R3,#0		;Check if R3 is zero
	BRz MULEND
LOOPADD
	ADD R0,R0,R4
	ADD R3,R3,#-1		;Add R4 into R0, R3 amount of times
	BRp LOOPADD			;
MULEND
	LD R3,MULTSaveR3	;Load R3 back into R3 after multiplication is done
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	ST R3, DIVSaveR3
	AND R2,R2,#0
	AND R0,R0,#0	;Clear R0
	ADD R4,R4,#0
	BRz ERROR
DIVLOOP				;Loop name
	ADD R0,R0,#1	;Increment R0
	NOT R2,R4		
	ADD R2,R2,#1	;Make R4 negative
	ADD R3,R3,R2	;Do R3-R4
	BRzp DIVLOOP	;If zero or pos, subtract again
	ADD R0,R0,#-1	;Decrement R0 b/c we increment 1 too many
	ADD R1,R3,R4	;Add the remainder into R1
	LD R3, DIVSaveR3
	RET

	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
	ST R3, EXP_SaveR3	;save R3
	ST R4, EXP_SaveR4	;save R4
	ADD R3,R3,#0
	BRz	EXPONE			;If R3 is zero, make R0 Zero
	ADD R4,R4,#-1
	BRn SOLONE			;If Exponent is zero, make R0 equal 1
	ADD R4,R4,#0
	BRz EXPONE			;If exponent is one, make R0 equal R3
	ADD R3,R3,#-1		
	BRz	SOLONE			;If R3 base number is one, make answer one
	LD R3, EXP_SaveR3
	LD R4, EXP_SaveR4	;Set R3 and R4 back to original values
	AND R0,R0,#0
	ADD R6,R4,#0
	ADD R6,R6,#-1		;Load R4-1 into R6 to make a counter
	LD R4, EXP_SaveR3	;Load R3 into R4
	BR LOOPEXPADD
LOOPEXP
	AND R3,R3,#0
	ADD R3,R0,#0
	ADD R6,R6,#-1		;Decrement the 'exponent' 
	BRnz EXPDONE
	LD R4, EXP_SaveR3
	ADD R4,R4,#-1		;Same code as addition basically
LOOPEXPADD
	ADD R0,R0,R3
	ADD R4,R4,#-1
	BRp LOOPEXPADD
	BR  LOOPEXP
EXPONE					;Catch if exponent is one
	AND R0,R0,#0
	ADD R0,R3,#0
	BR  EXPDone
SOLONE					;Catch if the answer should be one
	AND R0,R0,#0
	ADD R0,R0,#1
EXPDONE
	LD R3, EXP_SaveR3
	LD R4, EXP_SaveR4
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Placed here for the offset value
KBSR		.FILL xFE00 ;
KBDR		.FILL xFE02 ;
DSR			.FILL xFE04 ;
DDR			.FILL xFE06	;
INVALID		.STRINGZ "Invalid Expression" ;Holds the string to print Invalid Expression
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3			;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R4
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3			;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;
MULTSaveR3  .BLKW #1    ;
DIVSaveR3	.BLKW #1	;
EXP_SaveR3	.BLKW #1	;
EXP_SaveR4	.BLKW #1	;


.END
