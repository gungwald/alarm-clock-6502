;
; File generated by cc65 v 2.15 - Git 6f24c07
;
	.fopt		compiler,"cc65 v 2.15 - Git 6f24c07"
	.setcpu		"65C02"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	off
	.importzp	sp, sreg, regsave, regbank
	.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4
	.macpack	longbranch
	.forceimport	__STARTUP__
	.import		_stdout
	.import		_fputc
	.export		_main

; ---------------------------------------------------------------
; void __near__ main (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_main: near

.segment	"CODE"

	ldx     #$00
	lda     #$41
	jsr     pushax
	lda     _stdout
	ldx     _stdout+1
	jsr     _fputc
	rts

.endproc
