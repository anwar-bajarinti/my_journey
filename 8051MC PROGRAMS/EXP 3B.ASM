ORG 00H
    MOV TMOD,#61H         ; Timer 1: Mode 2, Timer 0: Mode 1
    SETB P3.5             ; Set P3.5 high
    MOV DPTR,#0FFC1H       ; External RAM address
    MOV TH1,#00H          ; Auto-reload value

AGAIN:
    SETB TR1              ; Start Timer 1

L2:
    ACALL DELAY           ; Timer 0 delay
    CPL P3.5              ; Toggle P3.5
    MOV A,TL1             ; Read Timer 1 low byte
    MOVX @DPTR,A          ; Store at DPTR
    MOV P2,A              ; Output to P2
    JNB TF1,L2            ; Repeat until Timer 1 overflow

    CLR TR1               ; Stop Timer 1
    CLR TF1               ; Clear overflow flag
    SJMP AGAIN            ; Repeat

; Delay using Timer 0
DELAY:
    MOV TL0,#1AH
    MOV TH0,#0FFH
    SETB TR0
HERE:
    JNB TF0,HERE
    CLR TF0
    CLR TR0
    RET

END
