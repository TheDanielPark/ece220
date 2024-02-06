;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

;Names:Daniel Park & Jay Patel
;Date: 9/3/19
;Course: ECE 220 MP1
;The goal of the project is to read a given string and print a histogram that displays how many
;letters were used each and how many non letters were used. We approached this project
;by completing lab1 to figure out how to print hex values. Then we used that base code
;to first print the letter that the hex represents, then we counted through the memory 
;to retrieve the correct hex and print that value next to the ascii character it corresponded
;to. 
;partners: jayhp2, danielp7

;R0 is the register that will hold the value in the histogram to print,
; print the space, print the new line, and print the letter correspoding to the histogram
;R1 is the counter to count to 4 for each bit
;R2 is the counter to keep incrementing @ till Z
;R3 is the register that holds the inital hex input
;R4 Big loop counter
;R5 holds the pointer to histogram
;R6 is the counter to 27
LD R5,HIST_ADDR
LD R6,NUM_BINS


     	AND R0,R0,#0 ;Clear R0
	 	AND R2,R2,#0 ;Clear R2
		ADD R5,R5,#-1 ;Subtract 1 so it adds and fits in the loop
		LD R2,HEX_AT_MINUS_ONE
NEXT
		ADD R6,R6,#-1 ;Decrement R6
		BRn DONE	 ;Branch to done if the counter ends
		LD R0,NEW_LINE ;New Line
		OUT			 ;Print the new line
		ADD R2,R2,#1 ;Add 1 to the hex value @-1 to get @. Then keep adding to get the future values 
		ADD R0,R2,#0 ;Put the correct ascii character into R0
		OUT			 ;Print the ascii character
		LD R0,SPACE	 ;Load a ascii space into R0
		OUT			 ;Print the space
		AND R0,R0,#0 ;Clear R0
		ADD R5,R5,#1 ;Increment R5
		LDR R3,R5,#0 ;Load memory of R5 into R3
		AND R4,R4,#0 ;Clear R4
		ADD R4,R4,#4 ;Set R4 to 4
BLOOP   ADD R4,R4,#-1 ;Bigger loop start to decrement the counter for 4 hex symbols
		BRn NEXT	 ;if the big counter loops 4 times it should go to the next memory location
		AND R1,R1,#0 ;clear R1
    	ADD R1,R1,#4 ;Add 4 to R1 to set the smaller loop counter
LOOP  				 ;start of small loop
		ADD R0,R0,R0 ;left shift R0
   	    ADD R3,R3,#0 ;add 0 to get the branch option
  	    BRzp POS  	 ;if R3 has a zero in the front go to the pos loop
  	    ADD R0,R0,#1 ;add a 1 to R0 if R3 has a 1 in front
    	ADD R3,R3,R3 ;left shift R3
   	    ADD R1,R1,#-1 ;decrement R1
   	    BRp LOOP	 ;if R1 hasn't decremented 4 times loop again
   	    BRnz PRINT   ;if R1 has then print
POS   	ADD R3,R3,R3 ;Left shift R3
      	ADD R1,R1,#-1 ;decrement R1
     	BRp LOOP	 ;if R1 hasn't decremented 4 times loop again
PRINT	AND R1,R1,#0 ;Clear R1
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
		BR  BLOOP    ;loop to big loop


DONE	HALT		 ; done


; the data needed by the program
NUM_BINS				.FILL #27	; 27 loop iterations
NEG_AT					.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z				.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ				.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR				.FILL x3F00 ; histogram starting address
STR_START				.FILL x4000	; string starting address
NEW_LINE				.FILL x000A ;New Line
HEX_AT_MINUS_ONE		.FILL x003F ;Hex for @ - 1
SPACE					.FILL x0020 ;Hex for space

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
