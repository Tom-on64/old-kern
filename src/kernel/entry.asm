[bits 32]

[extern main] ; Main from main.c
[extern idtp] ; IDT Pointer from idt.c
[extern faultHandler] ; Fault handler from isrs.c

; Calls main in main.c. If we return from main.c, halt
[global _start]
_start:
    call main
    jmp $

; ISRs
[global isr0]
[global isr1]
[global isr2]
[global isr3]
[global isr4]
[global isr5]
[global isr6]
[global isr7]
[global isr8]
[global isr9]
[global isr10]
[global isr11]
[global isr12]
[global isr13]
[global isr14]
[global isr15]
[global isr16]
[global isr17]
[global isr18]
[global isr19]
[global isr20]
[global isr21]
[global isr22]
[global isr23]
[global isr24]
[global isr25]
[global isr26]
[global isr27]
[global isr28]
[global isr29]
[global isr30]
[global isr31]
isr0:
    cli
    push 0
    push 0
    jmp isrCommon
isr1:
    cli
    push 0
    push 1
    jmp isrCommon
isr2:
    cli
    push 0
    push 2
    jmp isrCommon
isr3:
    cli
    push 0
    push 3
    jmp isrCommon
isr4:
    cli
    push 0
    push 4
    jmp isrCommon
isr5:
    cli
    push 0
    push 5
    jmp isrCommon
isr6:
    cli
    push 0
    push 6
    jmp isrCommon
isr7:
    cli
    push 0
    push 7
    jmp isrCommon
isr8:
    cli
    push 8
    jmp isrCommon
isr9:
    cli
    push 0
    push 9
    jmp isrCommon
isr10:
    cli
    push 10
    jmp isrCommon
isr11:
    cli
    push 11
    jmp isrCommon
isr12:
    cli
    push 12
    jmp isrCommon
isr13:
    cli
    push 13
    jmp isrCommon
isr14:
    cli
    push 14
    jmp isrCommon
isr15:
    cli
    push 0
    push 15
    jmp isrCommon
isr16:
    cli
    push 0
    push 16
    jmp isrCommon
isr17:
    cli
    push 0
    push 17
    jmp isrCommon
isr18:
    cli
    push 0
    push 18
    jmp isrCommon
isr19:
    cli
    push 0
    push 19
    jmp isrCommon
isr20:
    cli
    push 0
    push 20
    jmp isrCommon
isr21:
    cli
    push 0
    push 21
    jmp isrCommon
isr22:
    cli
    push 0
    push 22
    jmp isrCommon
isr23:
    cli
    push 0
    push 23
    jmp isrCommon
isr24:
    cli
    push 0
    push 24
    jmp isrCommon
isr25:
    cli
    push 0
    push 25
    jmp isrCommon
isr26:
    cli
    push 0
    push 26
    jmp isrCommon
isr27:
    cli
    push 0
    push 27
    jmp isrCommon
isr28:
    cli
    push 0
    push 28
    jmp isrCommon
isr29:
    cli
    push 0
    push 29
    jmp isrCommon
isr30:
    cli
    push 0
    push 30
    jmp isrCommon
isr31:
    cli
    push 0
    push 31
    jmp isrCommon

isrCommon:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, faultHandler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

; Loads the IDT
[global idtLoad]
idtLoad:
    lidt [idtp]
    ret
