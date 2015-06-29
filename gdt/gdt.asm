
%include "gdt.inc"


org 07c00h
;jmp LABEL_BEGIN

[SECTION .gdt]

LABEL_GDT:        Descriptor 0,       0, 0
LABEL_DESC_CODE:  Descriptor 0,       SegCodeLen - 1, DA_C + DA_32
LABEL_DESC_VIDEO: Descriptor 0B8000h, 0ffffh, DA_DRW


Gdtlen equ $-LABEL_GDT
Gdtptr dw Gdtlen-1
       dd 0

SelectorCode   equ  LABEL_DESC_CODE-LABEL_GDT
SelectorVideo  equ  LABEL_DESC_VIDEO-LABEL_GDT

;end [section .gdt]

[SECTION .s16]
[BITS 16]
LABLE_BEGIN:


    jmp SelectorCode:0

[SECTION .s32]
[BITS 32]
LABEL_SEG_CODE:



    jmp $

SegCodeLen equ $-LABEL_SEG_CODE

;times   510-($-$$)  db  0   ; 填充剩下的空间，使生成的二进制代码恰好为512字节
;dw  0xaa55              ; 结束标志
