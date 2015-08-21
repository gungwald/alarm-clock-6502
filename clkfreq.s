rgConfig        =       $6000   ; write: D6=1 - NMI is off, D6=0 - NMI is on
rgStatus        =       $6000   ; read:  D6=0 - UART is busy
rgTxD           =       $5000   ; write: data to send via UART

vcNMI           =       $FFFA

Refresh         =       450     ; NMI rate in Hz

.export _clkfreq
.export _ticks
_clkfreq:
        ldx     #<NMI           ; installing the NMI vector
        ldy     #>NMI
        stx     vcNMI
        sty     vcNMI+1
        lda     #$40            ; on start NMI is off
        sta     InUse

Again:
        lda     #0
        sta     Flag
        sta     _ticks          ; initializing counter
        sta     _ticks+1
        sta     _ticks+2
        sta     _ticks+3
        lda     #$FE            ; initializing NMI counter (zeropoint minus 2 ticks)
        sta     Timer
        lda     #$FF
        sta     Timer+1
        lda     InUse           ; turn on NMI
        and     #$BF
        sta     rgConfig
        sta     InUse

L1:     bit     Flag            ; waiting for zeropoint minus 1 tick
        bpl     L1
        lda     #0
        sta     Flag

L2:     bit     Flag            ; waiting for true zeropoint
        bpl     L2
        lda     #0
        sta     Flag

Main:                           ; main counting cycle
;number of ticks per command   sum of ticks
;                          v   v
        lda     _ticks     ;4
        clc               ;2   6
        sed               ;2   8
        adc     #$53      ;2  10
        sta     _ticks     ;4  14
        lda     _ticks+1   ;4  18
        adc     #0        ;2  20
        sta     _ticks+1   ;4  24
        lda     _ticks+2   ;4  28
        adc     #0        ;2  30
        sta     _ticks+2   ;4  34
        lda     _ticks+3   ;4  38
        adc     #0        ;2  40
        sta     _ticks+3   ;4  44
        cld               ;2  46
        bit     Flag      ;4  50
        bpl     Main      ;3  53

        lda     #0        ;2
        sta     Flag      ;4   6
        lda     _ticks     ;4  10
        clc               ;2  12
        sed               ;2  14
        adc     #$95      ;2  16
        sta     _ticks     ;4  20
        lda     _ticks+1   ;4  24
        adc     #0        ;2  26
        sta     _ticks+1   ;4  30
        lda     _ticks+2   ;4  34
        adc     #0        ;2  36
        sta     _ticks+2   ;4  40
        lda     _ticks+3   ;4  44
        adc     #0        ;2  46
        sta     _ticks+3   ;4  50
        cld               ;2  52
        lda     Timer     ;4  56
        cmp     #<Refresh ;2  58
        bne     Main      ;3  61 + 34 (from NMI ISR) = 95
        lda     Timer+1   ; 4
        cmp     #>Refresh ; 2
        bne     Main      ; 3

        lda     InUse           ; turn off NMI
        ora     #$40
        sta     rgConfig
        sta     InUse

        ldx     #0              ; send first string to the host
L3:     lda     Mes1,x
        beq     L4
        jsr     Send
        inx
        jmp     L3

L4:     lda     _ticks+3
        pha
        lsr
        lsr
        lsr
        lsr
        beq     L5              ; delete non-significant zero (clock < 10MHz)
        jsr     PrintDigit
L5:     pla
        and     #15
        jsr     PrintDigit
        lda     #'.'            ; decimal point
        jsr     Send
        lda     _ticks+2
        jsr     PrintTwoDigits
        lda     _ticks+1
        jsr     PrintTwoDigits
        lda     _ticks
        jsr     PrintTwoDigits

        ldx     #0              ; send second string to the host
L6:     lda     Mes2,x
        beq     L7
        jsr     Send
        inx
        jmp     L6
L7:     jmp     Again           ; repeat process

PrintTwoDigits:
        pha
        lsr
        lsr
        lsr
        lsr
        jsr     PrintDigit
        pla
        and     #15
        jsr     PrintDigit
        rts

PrintDigit:
        ora     #$30
        jsr     Send
        rts

Send:
        bit     rgStatus
        bvc     Send
        sta     rgTxD
        rts

Mes1:
        .byte   13
        .byte   "Current clock frequency is "
        .byte   0

Mes2:
        .byte   " MHz"
        .byte   0

_ticks:  .res    4,0
Timer:  .res    2,0
InUse:  .byte   0
Flag:   .byte   0

NMI:                       ;6
        pha                ;3   9
        inc     Timer      ;6  15
        bne     L8         ;3  18
        inc     Timer+1    ; 5
L8:     lda     #$80       ;2  20
        sta     Flag       ;4  24
        pla                ;4  28
        rti                ;6  34
