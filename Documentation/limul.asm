                 C?LIMUL:
C:0x0ACC    EC       MOV      A,R4
C:0x0ACD    8EF0     MOV      0xF0,R6
C:0x0ACF    A4       MUL      AB
C:0x0AD0    CC       XCH      A,R4
C:0x0AD1    C5F0     XCH      A,0xF0
C:0x0AD3    CC       XCH      A,R4
C:0x0AD4    CD       XCH      A,R5
C:0x0AD5    F8       MOV      R0,A
C:0x0AD6    EF       MOV      A,R7
C:0x0AD7    A4       MUL      AB
C:0x0AD8    CE       XCH      A,R6
C:0x0AD9    C5F0     XCH      A,0xF0
C:0x0ADB    2D       ADD      A,R5
C:0x0ADC    FD       MOV      R5,A
C:0x0ADD    E4       CLR      A
C:0x0ADE    3C       ADDC     A,R4
C:0x0ADF    FC       MOV      R4,A
C:0x0AE0    E8       MOV      A,R0
C:0x0AE1    A4       MUL      AB
C:0x0AE2    2E       ADD      A,R6
C:0x0AE3    C8       XCH      A,R0
C:0x0AE4    C5F0     XCH      A,0xF0
C:0x0AE6    3D       ADDC     A,R5
C:0x0AE7    FD       MOV      R5,A
C:0x0AE8    E4       CLR      A
C:0x0AE9    3C       ADDC     A,R4
C:0x0AEA    FC       MOV      R4,A
C:0x0AEB    EF       MOV      A,R7
C:0x0AEC    A4       MUL      AB
C:0x0AED    FF       MOV      R7,A
C:0x0AEE    E5F0     MOV      A,0xF0
C:0x0AF0    28       ADD      A,R0
C:0x0AF1    FE       MOV      R6,A
C:0x0AF2    E4       CLR      A
C:0x0AF3    3D       ADDC     A,R5
C:0x0AF4    FD       MOV      R5,A
C:0x0AF5    E4       CLR      A
C:0x0AF6    3C       ADDC     A,R4
C:0x0AF7    FC       MOV      R4,A
C:0x0AF8    22       RET      