                 C?UIDIV:
C:0x0A3E    BC000B   CJNE     R4,#0x00,C:0A4C
C:0x0A41    BE0029   CJNE     R6,#0x00,C:0A6D
C:0x0A44    EF       MOV      A,R7
C:0x0A45    8DF0     MOV      0xF0,R5
C:0x0A47    84       DIV      AB
C:0x0A48    FF       MOV      R7,A
C:0x0A49    ADF0     MOV      R5,0xF0
C:0x0A4B    22       RET      
C:0x0A4C    E4       CLR      A
C:0x0A4D    CC       XCH      A,R4
C:0x0A4E    F8       MOV      R0,A
C:0x0A4F    75F008   MOV      0xF0,#0x08
C:0x0A52    EF       MOV      A,R7
C:0x0A53    2F       ADD      A,R7
C:0x0A54    FF       MOV      R7,A
C:0x0A55    EE       MOV      A,R6
C:0x0A56    33       RLC      A
C:0x0A57    FE       MOV      R6,A
C:0x0A58    EC       MOV      A,R4
C:0x0A59    33       RLC      A
C:0x0A5A    FC       MOV      R4,A
C:0x0A5B    EE       MOV      A,R6
C:0x0A5C    9D       SUBB     A,R5
C:0x0A5D    EC       MOV      A,R4
C:0x0A5E    98       SUBB     A,R0
C:0x0A5F    4005     JC       C:0A66
C:0x0A61    FC       MOV      R4,A
C:0x0A62    EE       MOV      A,R6
C:0x0A63    9D       SUBB     A,R5
C:0x0A64    FE       MOV      R6,A
C:0x0A65    0F       INC      R7
C:0x0A66    D5F0E9   DJNZ     0xF0,C:0A52
C:0x0A69    E4       CLR      A
C:0x0A6A    CE       XCH      A,R6
C:0x0A6B    FD       MOV      R5,A
C:0x0A6C    22       RET      
C:0x0A6D    ED       MOV      A,R5
C:0x0A6E    F8       MOV      R0,A
C:0x0A6F    F5F0     MOV      0xF0,A
C:0x0A71    EE       MOV      A,R6
C:0x0A72    84       DIV      AB
C:0x0A73    20D21C   JB       0xD0.2,C:0A92
C:0x0A76    FE       MOV      R6,A
C:0x0A77    ADF0     MOV      R5,0xF0
C:0x0A79    75F008   MOV      0xF0,#0x08
C:0x0A7C    EF       MOV      A,R7
C:0x0A7D    2F       ADD      A,R7
C:0x0A7E    FF       MOV      R7,A
C:0x0A7F    ED       MOV      A,R5
C:0x0A80    33       RLC      A
C:0x0A81    FD       MOV      R5,A
C:0x0A82    4007     JC       C:0A8B
C:0x0A84    98       SUBB     A,R0
C:0x0A85    5006     JNC      C:0A8D
C:0x0A87    D5F0F2   DJNZ     0xF0,C:0A7C
C:0x0A8A    22       RET      
C:0x0A8B    C3       CLR      C
C:0x0A8C    98       SUBB     A,R0
C:0x0A8D    FD       MOV      R5,A
C:0x0A8E    0F       INC      R7
C:0x0A8F    D5F0EA   DJNZ     0xF0,C:0A7C
C:0x0A92    22       RET      