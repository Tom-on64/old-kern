[org 0x7c00]
[bits 16]
[global _start]

_start:
    ; Set up the stack
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov bp, 0x9000
    mov sp, bp

    ; Text mode (clears screen)
    mov ah, 0
    mov al, 3
    int 0x10

    ; Load kernel to KERNEL_LOC
    mov bx, KERNEL_LOC
    mov ah, 2   ; Read from disk
    mov al, 20  ; Read 20 sectors (! If code is more than 10kB it won't be fully loaded !)
    mov ch, 0   ; Cylinder number
    mov cl, 2   ; Sector to start at
    mov dh, 0   ; Head number
    int 0x13    ; Read interupt

    cli
    lgdt [GDT_Descriptor]
    ; Change last bit of cr0 to 1
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    ; Far jump to code
    call CODE_SEG:protected_start ; We never return
    jmp $

[bits 32]
protected_start:
    ; Set up data and stack segments
    mov ax, DATA_SEG 
    mov ds, ax 
    mov ss, ax 
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Set up the stack pointer in protected mode
    mov ebp, 0x90000
    mov esp, ebp

    ; Perform the far jump
    jmp KERNEL_LOC
    jmp $

; Global Descriptor Table
GDT_Start:
    null_descriptor:
        dd 0 ; four null bytes
        dd 0 ; four null bytes
    code_descriptor:
        dw 0xffff ; First bits of limit
        dw 0 ; 16 bits +
        db 0 ; + 8 bits = 24 bits
        db 0b10011010 ; p, p, t, type flags
        db 0b11001111 ; Other flags + limit (last 4 bits)
        db 0 ; base (last 8 bits)
    data_descriptor:
        dw 0xffff ; First bits of limit
        dw 0 ; 16 bits +
        db 0 ; + 8 bits = 24 bits
        db 0b10010010 ; p, p, t, type flags
        db 0b11001111 ; Other flags + limit (last 4 bits)
        db 0 ; base (last 8 bits)
GDT_End:

GDT_Descriptor:
    dw GDT_End - GDT_Start - 1  ; Size
    dd GDT_Start    

CODE_SEG equ code_descriptor - GDT_Start
DATA_SEG equ data_descriptor - GDT_Start
KERNEL_LOC equ 0x1000

times 510 - ($ - $$) db 0
db 0x55, 0xaa
