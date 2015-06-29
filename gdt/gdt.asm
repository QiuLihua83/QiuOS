
%include "gdt.inc"


org 07c00h
jmp LABEL_BEGIN

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
LABEL_BEGIN:
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0100h

    xor eax, eax
    mov ax, cs
    shl eax, 4
    add eax, LABEL_SEG_CODE
    mov word [LABEL_DESC_CODE+2], ax
    shr eax, 16
    mov byte [LABEL_DESC_CODE+4], al
    mov byte [LABEL_DESC_CODE+7], ah

    xor eax, eax
    mov ax, ds
    shl eax, 4
    add eax, LABEL_GDT
    mov dword [Gdtptr+2], eax

    lgdt  [Gdtptr]

    cli

    in al, 92h
    or al, 00000010b
    out 92h, al

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp SelectorCode:0

[SECTION .s32]
[BITS 32]
LABEL_SEG_CODE:
    mov ax, SelectorVideo
    mov gs,ax
    mov edi, (80*6+20)*2
    mov ah, 0Ch
    mov al,'Q'
    mov [gs:edi], ax

    jmp $

SegCodeLen equ $-LABEL_SEG_CODE

;times   510-($-$$)  db  0   ; 填充剩下的空间，使生成的二进制代码恰好为512字节
;dw  0xaa55              ; 结束标志
