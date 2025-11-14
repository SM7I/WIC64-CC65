; win64lib-asm.s — assembly routines matching XC Basic inline ASM behavior

.export _setbyte, _readbyte
.export _wic_port_send_setup, _wic_port_recv_setup, _wic_irq_clear, _wic_cli

PRA  = $dd00
PRB  = $dd01
DDRA = $dd02
DDRB = $dd03
ICR  = $dd0d

.segment "CODE"

_wic_port_send_setup:
    lda DDRA
    ora #$04
    sta DDRA
    lda PRA
    ora #$04
    sta PRA
    lda #$ff
    sta DDRB
    lda ICR
    rts

_wic_port_recv_setup:
    lda #$00
    sta DDRB
    lda PRA
    and #$fb
    sta PRA
    sei
    rts

_wic_irq_clear:
    lda ICR
    rts

; __fastcall__: byte arg is passed in A
_setbyte:
    sta PRB
@wait1:
    lda ICR
    and #$10
    beq @wait1
    rts

_readbyte:
@waitr:
    lda ICR
    and #$10
    beq @waitr
    lda PRB
    rts

_wic_cli:
    cli
    rts

