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

;
; Reads a user input string terminated by a newline
; Args:
;   bx - Pointer to buffer
; Returns: Read string into the buffer
;
reads:
    push ax
    mov al, 0
.loop:
    cmp al, 0x0d
    je .done
    mov ah, 0
    int 0x16
    mov ah, 0x0e
    int 0x10
    mov [bx], al
    inc bx
    jmp .loop
.done:
    mov ah, 0x0e
    mov al, [newline]
    int 0x10
    mov al, 0
    dec bx
    mov [bx], al
    pop ax
    ret

newline: db 0x0a, 0x0d