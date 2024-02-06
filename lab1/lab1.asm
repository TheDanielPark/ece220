; write your code here
;R0 is the register that will hold the value in R3 to print
;R1 is the counter to count to 4 for each bit
;R2 Temp storage register
;R3 is the register that holds the inital hex input
;R4 Big loop counter
		.ORIG x3000     	

     	AND R0,R0,#0 ;Clear R0
	 	AND R2,R2,#0 ;Clear R2
		AND R4,R4,#0 ;Clear R4
		ADD R4,R4,#4 ;Set R4 to 4
BLOOP   ADD R4,R4,#-1 ;Bigger loop start to decrement the counter for 4 hex symbols
		BRn STOP	 ;if the big counter loops 4 times it should stop
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
STOP	HALT		 ;stop the program
.END

