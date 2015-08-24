.forceimport	__STARTUP__
.export         _main

.segment    "RODATA"

; All numbers are going to be this size and type.
Unsigned_Integer_Size = 4
; Standard character output routine
COUT = $fded

.segment    "BSS"

Sleep_Loop_Count: .res Unsigned_Integer_Size,0 ; Byte values initialized to 0

; *************************************
;
;   Macros
;
; *************************************

; Number++
.macro Increment Number
    .local Next_Byte
    .local Done
    ldx #0                      ; X := 0
Next_Byte:
    inc Number,X                ; Increment the value at Count+X address
    bne Done                    ; Incrementing Count did not cause it to roll over to 0.
    inx                         ; Increment X to the next byte
    cpx #Unsigned_Integer_Size  ; Compare X with 4.
    bmi Next_Byte               ; If X < Count_Size continue with next byte.
Done:
.endmacro

; Minuend = Minuend - Subtrahend
.macro Subtract Minuend, Subtrahend
    .local Next_Byte
    ldx #0
    clc
Next_Byte:
    lda Addr1,X
    sbc Addr2,X
    inx
    cpx #Unsigned_Integer_Size
    bmi Next_Byte
.endmacro

; *************************************
;
;   Main
;
; *************************************

.segment    "CODE"

.proc   _main:  near

.segment    "CODE"

Sleep_Loop:

; Do nothing 10 times.

    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop

    Increment Sleep_Loop_Count
    lda #1
    cmp Sleep_Loop_Count+3
    bmi Sleep_Loop

; Output result

    ldx #0
Next_Byte:
    lda Sleep_Loop_Count,X
    jsr COUT
    inx
    cpx #Unsigned_Integer_Size
    bmi Next_Byte

    rts ; from _main

.endproc

