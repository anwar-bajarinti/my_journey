ORG 00H            ; Program starts at address 0000H

MOV TMOD, #06H     ; TMOD = 0000 0110
                   ; - Timer 0 in Mode 2 (8-bit auto-reload)
                   ; - Timer 1 unused
MOV DPTR, #0FC1H  ; Load DPTR (Data Pointer) with address 0FFC1H
MOV TH0, #00H      ; Load TH0 = 00H (reload value for Timer 0)
;SETB P3.4          ; Set P3.4 = 1 (possibly to enable something or as an output)

AGAIN: 
    SETB TR0       ; Start Timer 0

BACK: 
    MOV A, TL0     ; Move Timer 0 low byte into Accumulator
    MOVX @DPTR, A   ; Store A into external RAM at address 0FFC1H
    MOV P2, A      ; Output the value of A to Port 2
    JNB TF0, BACK  ; Keep looping until Timer 0 overflows (TF0=1)

    CLR TR0        ; Stop Timer 0
    CLR TF0        ; Clear overflow flag
    SJMP AGAIN     ; Repeat the process

END                ; End of program
