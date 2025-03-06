.model tiny
.code
org 100h

main:
    ; Вывод сообщения "Enter password: "
    mov dx, offset prompt_msg
    mov ah, 09h
    int 21h

    push 1   ; right_password_flag = 0

    ; Читаем ввод с клавиатуры в цикле при помощи 21h 01h
    lea di, input_pass
    dec di
    mov ah, 01h

input_loop:
    inc di
    int 21h
    cmp al, 0dh
    je change_enter
    mov ds:[di], al
    jmp input_loop

    ; Убираем Enter (0Dh) и заменяем его на 0
change_enter:
    xor al, al
    mov ds:[di], al

    ; Сравниваем строки
    lea si, input_pass
    lea di, correct_pass

compare_loop:

    mov al, [si]   ; Загружаем символы из введённой строки
    mov bl, [di]
    sub al, 20h    ; Делаем смещение al на 20h (32d) для кодирования пароля из данных проги
    cmp al, 0      ; Если встретили `0` — пароли совпали
    je check
    cmp al, bl     ; Если символы не равны — переход на `wrong`
    jne differ_letters
continue_comp:
    inc si
    inc di
    jmp compare_loop

check:

    pop ax    ; Вытаскиваем rigth_password_flag из стека
    cmp ax, 1 ; Проверяем, чему он равен
    jne wrong


correct:

    mov dx, offset success_msg
    mov ah, 09h
    int 21h
    jmp exit

wrong:

    mov dx, offset fail_msg
    mov ah, 09h
    int 21h

exit:

    mov ax, 4c00h
    int 21h

differ_letters:

    mov bp, sp              ;кладём в bp регистр sp, чтобы получить доступ к ячейке стека
    mov word ptr [bp], 0    ;заменяем 1 на ноль у флага rigth_password
    jmp continue_comp       ;возвращаемся к сравнению


.data
    prompt_msg      db "Enter password:      $"
    success_msg     db "Correct password!", 13, 10, "$"
    fail_msg        db "Wrong password!", 13, 10, "$"
    input_pass      db 9      ; Максимальная длина ввода (9 символов)
                    db 0      ; Фактическая длина (заполняется DOS)
                    db 10 dup(?)  ; Буфер для символов (8 символов + Enter + запас)
    correct_pass    db "ABCDEFGH", 0  ; Верный пароль

end main