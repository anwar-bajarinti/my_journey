ORG 0000H

; Example: 4-digit ID stored at 30H to 33H
; 30H = 01H, 31H = 02H, 32H = 03H, 33H = 04H

MOV R0, #30H      ; Pointer to ID digits
MOV A, @R0        ; Load first digit
INC R0
ADD A, @R0        ; Add second digit
INC R0
ADD A, @R0        ; Add third digit
INC R0
ADD A, @R0        ; Add fourth digit

DA A              ; Convert result to BCD (if needed)

MOV R3, A         ; Save final BCD result in R3

SJMP $

END
