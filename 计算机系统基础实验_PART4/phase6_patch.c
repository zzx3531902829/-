// phase6_patch.c
#include <stdio.h>

// 定义实际的打印函数
void myprint_impl() {
    printf("U202414649\n");
}

// 定义函数指针变量myprint，指向myprint_impl
void (*myprint)() = myprint_impl;