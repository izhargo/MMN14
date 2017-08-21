.entry LOOP
MAIN: inc K
       mov M1[r2][r7],W
.extern W a
      add r2,STR
	lea LOOP, K, STR 
LOOP: jmp W
      prn 
STR: .string "ab"
     sub r1,r4
     stop
	dec M1[r3][8a]
.entry GT1
K: .data 2,7
	.data 
STR:	.string "cd"
M1: .mat [2][2] 1,2,3,4
  .data 4d
