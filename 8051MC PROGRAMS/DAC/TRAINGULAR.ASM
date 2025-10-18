ORG 0000H

MAIN:
    MOV A,#00H         ; Start from 0

AGAIN:
; ----------- UP RAMP ------------
UP_LOOP:
    MOV P1,A           ; Output to DAC
    INC A              ; Increment
    ACALL DELAY
    CJNE A,#0FFH,UP_LOOP  ; Until A = 0xFF

; ----------- DOWN RAMP ----------
DOWN_LOOP:
    MOV P1,A           ; Output current value (255 first)
    DEC A              ; Decrement
    ACALL DELAY
    CJNE A,#00H,DOWN_LOOP  ; Until A = 0x00

    SJMP AGAIN         ; Repeat (no reinitialization!)
; ----------- DELAY --------------
DELAY:
    MOV R0,#90H
W1: MOV R1,#0FFH
W2: MOV R2,#0FFH
W3: DJNZ R2,W3
    DJNZ R1,W2
    DJNZ R0,W1
    RET
END
