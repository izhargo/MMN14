.ENTRY LOOP
MAIN: INC K
       mov M1[r2][r7],W
.EXTERN W
      ADD R2,STR
LOOP: JMP W
      PRN #-5
STR:.STRING "ab"
     SUB R1,R4
     STOP
.ENTRY STR
K: .DATA 2,7
M1: .MAT[2][2] 1,2,3,4
