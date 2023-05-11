global mystrcmp
section .text

;-----------------------------------
; Compares two 32-byte strings
;-----------------------------------
; Entry:    rdi = string 1
;           rsi = string 2
;
; Exit:     rax  = 0 if strings are equal
;           rax != 0 if not
;
;-----------------------------------


mystrcmp:   

        mov rax, qword [rdi]
        xor rax, qword [rsi]

        jnz Return

        mov rax, qword [rdi + 8]
        xor rax, qword [rsi + 8]

        jnz Return

        mov rax, qword [rdi + 16]
        xor rax, qword [rsi + 16]

        jnz Return

        mov rax, qword [rdi + 24]
        xor rax, qword [rsi + 24]

Return: ret