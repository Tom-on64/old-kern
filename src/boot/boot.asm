[org 0x7c00]
[bits 16]

start:
    ; Set up the stack
    mov bp, 0x8000
    mov sp, bp

    mov bx, msg
    call puts

halt:
    jmp $

;
; Prints a string to the screen
; Args:
;   bx - String pointer
;
puts:
    push ax
    mov ah, 0x0e
.loop: 
    mov al, [bx]
    or al, al
    jz .done
    int 0x10
    inc bx
    jmp .loop
.done: 
    pop ax
    ret

msg: db "Hello, World!", 0

times 510 - ($ - $$) db 0
db 0x55, 0xaa
