; Это восстановленная программа по .com файлу для упрощения взлома и тестов crack.c

.model tiny
.code
org 100h
locals
.186

main proc

    push 5
    call paswordCheck
    pop ax

    mov ax, 4c00h
    int 21h 

endp

paswordCheck proc

    sub sp, 30
    mov ax, offset rightPassword + passwordLenth - 1
    push ax
    mov lastSymbol, sp
    sub sp, 30
    mov passwordBufferptr, sp
    mov ax, 255
    mov bx, sp
    mov [bx], al


    mov dx, passwordBufferptr
    mov ah, 0Ah
    int 21h

    add sp, 62

    mov si, passwordBufferptr
    add si, 2
    mov di, offset rightPassword
    mov ax, ds
    mov es, ax

    mov bx, lastSymbol
    mov bx, [bx]

    jmp test1
    

compare:

    cmpsb
    jne wrongPassword

test1:
    cmp bx, di    
    ja compare

    mov dx, offset successString
    jmp endl

wrongPassword:
    mov dx, offset failureString

endl:
    mov ah, 09h
    int 21h

ret    
endp

.data

failureString  db 'access denied$'
successString  db 'access allowed$'

needchange     db  1

rightPassword db 'testpassword'
lastSymbol    dw 0
passwordLenth  equ 12
passwordBufferptr dw 0 
attemts        db  1

end main    