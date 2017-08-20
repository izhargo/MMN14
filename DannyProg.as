.entry LOOP
MAIN: inc K
       mov M1[r2][r7],W
.extern W
      add R2,STR
LOOP: jmp W
      prn #-5
STR:.string "ab"
     sub R1,R4
     stop
.entry STR
K: .data 2,7
M1: .mat[2][2] 1,2,3,4
