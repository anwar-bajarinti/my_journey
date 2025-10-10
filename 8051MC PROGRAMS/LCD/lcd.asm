;----------------------------------------
; 8051 Program to Display "ANWAR" on LCD
; LCD connected in 8-bit mode
; RS -> P3.7
; RW -> P3.6
; EN -> P3.5
; Data -> P2
;----------------------------------------

ORG 0400H               ; Store string in program memory
MSG: DB "ANWAR",0       ; String to display

ORG 0000H               ; Program execution starts here
MAIN:
    MOV DPTR,#MSG       ; Load DPTR with address of string
                        
    ;---- LCD Initialization ----
    MOV A,#38H          ; Function Set (8-bit, 2 lines, 5x7 dots)
    ACALL CMD
    MOV A,#01H          ; Clear display
    ACALL CMD
    MOV A,#0FH          ; Display ON, cursor ON, blink ON
    ACALL CMD
    MOV A,#06H          ; Entry mode (cursor right)
    ACALL CMD
    MOV A,#82H          ; Cursor at 1st row, 2nd position
    ACALL CMD

    ;---- Display Loop ----
    MOV R7,#05H         ; Number of characters = 5 ("ANWAR")
    MOV R0,#00H

BACK: 
    MOV A,R0
    MOVC A,@A+DPTR      ; Fetch character from code memory
    ACALL INFO          ; Send to LCD
    INC R0
    DJNZ R7,BACK        ; Repeat until all characters displayed

    SJMP $              ; Infinite loop (stop program here)

;----------------------------------------
; SUBROUTINE: Send Command to LCD
;----------------------------------------
CMD:
    CLR P3.7            ; RS = 0 (command)
    CLR P3.6            ; RW = 0 (write)
    MOV P2,A            ; Put command on data pins
    SETB P3.5           ; EN = 1
    CLR P3.5            ; EN = 0 (latch command)
    ACALL DELAY
    RET

;----------------------------------------
; SUBROUTINE: Send Data (character) to LCD
;----------------------------------------
INFO:
    SETB P3.7           ; RS = 1 (data)
    CLR P3.6            ; RW = 0 (write)
    MOV P2,A            ; Put data on data pins
    SETB P3.5           ; EN = 1
    CLR P3.5            ; EN = 0 (latch data)
    ACALL DELAY
    RET

;----------------------------------------
; SUBROUTINE: Delay
;----------------------------------------
DELAY:
    MOV R1,#0FFH
WAIT1: 
    MOV R2,#0FFH
WAIT2: 
    DJNZ R2,WAIT2
    DJNZ R1,WAIT1
    RET

END