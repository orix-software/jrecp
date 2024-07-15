.export _display_pic

.import popa
.importzp ptr1, ptr2, tmp1, tmp2, tmp3, tmp4

; extern void display_pic(unsigned char x, unsigned char y, unsigned char length, unsigned char height, unsigned char pic[]);
.proc _display_pic
    height := tmp4
    length := tmp1
    posx := tmp2
    posy := tmp3

    sta     ptr1
    stx     ptr1+1

    jsr     popa
    sta     height

    jsr     popa
    sta     length

    lda     #<$A000
    sta     ptr2
    lda     #>$A000
    sta     ptr2+1

    jsr     popa
    sta     posy

    jsr     popa
    clc
    adc     ptr2
    bcc     @S3
    inc     ptr2+1
@S3:
    sta     ptr2

    ldx     posy
@L5:
    lda     #$28
    clc
    adc     ptr2
    bcc     @S4
    inc     ptr2+1
@S4:
    sta     ptr2
    dex
    bpl     @L5



    ldx     #$00

@L2:
    ldy     #$00
@L1:
    lda     (ptr1),y
    sta     (ptr2),y
    iny
    cpy     length
    bne     @L1

    tya
    clc
    adc     ptr1
    bcc     @S1
    inc     ptr1+1
@S1:
    sta     ptr1

    lda     #$28
    clc
    adc     ptr2
    bcc     @S2
    inc     ptr2+1
@S2:
    sta     ptr2
    inx
    cpx     height
    bne     @L2

    rts
.endproc