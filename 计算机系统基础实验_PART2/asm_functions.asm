section .text
global calculate_averages_asm

; void calculate_averages_asm(struct student *students, int count)
calculate_averages_asm:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    push r13
    push r14

    ; rdi = students
    ; esi = count
    mov rbx, rdi        ; rbx = 学生数组指针
    mov r12d, esi       ; r12 = 学生数量

    xor r13, r13        ; 学生索引
student_loop:
    cmp r13d, r12d
    jge end_loop

    ; 计算单个学生的总分
    xor r14d, r14d      ; 总分
    mov ecx, 8          ; 8门课程
    lea rax, [rbx + r13 * 32 + 16] ; scores数组地址 (32=结构体大小)

course_loop:
    add r14w, word [rax]
    add rax, 2
    loop course_loop

    ; 计算平均分
    mov eax, r14d
    mov ecx, 8
    xor edx, edx
    div ecx
    mov [rbx + r13 * 32 + 32 - 2], ax ; 存储平均分 (结构体最后2字节)

    inc r13
    jmp student_loop

end_loop:
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp
    ret