                 C?IMUL:
C:0x0A2C    EF       MOV      A,R7
C:0x0A2D    8DF0     MOV      0xF0,R5
C:0x0A2F    A4       MUL      AB
C:0x0A30    A8F0     MOV      R0,0xF0
C:0x0A32    CF       XCH      A,R7
C:0x0A33    8CF0     MOV      0xF0,R4
C:0x0A35    A4       MUL      AB
C:0x0A36    28       ADD      A,R0
C:0x0A37    CE       XCH      A,R6
C:0x0A38    8DF0     MOV      0xF0,R5
C:0x0A3A    A4       MUL      AB
C:0x0A3B    2E       ADD      A,R6
C:0x0A3C    FE       MOV      R6,A
C:0x0A3D    22       RET      