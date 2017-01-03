          C?ULSHR:
C:0x0A93    E8       MOV      A,R0
C:0x0A94    600F     JZ       C:0AA5
C:0x0A96    EC       MOV      A,R4
C:0x0A97    C3       CLR      C
C:0x0A98    13       RRC      A
C:0x0A99    FC       MOV      R4,A
C:0x0A9A    ED       MOV      A,R5
C:0x0A9B    13       RRC      A
C:0x0A9C    FD       MOV      R5,A
C:0x0A9D    EE       MOV      A,R6
C:0x0A9E    13       RRC      A
C:0x0A9F    FE       MOV      R6,A
C:0x0AA0    EF       MOV      A,R7
C:0x0AA1    13       RRC      A
C:0x0AA2    FF       MOV      R7,A
C:0x0AA3    D8F1     DJNZ     R0,C:0A96
C:0x0AA5    22       RET      