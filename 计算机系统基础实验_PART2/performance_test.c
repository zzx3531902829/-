#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define N 10000
#define COURSES 8
#define WARMUP 100
#define ITERATIONS 1000

struct student {
    char name[8];
    char sid[12];
    short scores[COURSES];
    short average;
};

// 函数声明
void calculate_averages_c(struct student *students, int count);
extern void calculate_averages_asm(struct student *students, int count);
extern void calculate_averages_asm_opt1(struct student *students, int count);
extern void calculate_averages_asm_opt2(struct student *students, int count);

// C版本计算平均成绩的实现
void calculate_averages_c(struct student *students, int count) {
    for (int i = 0; i < count; i++) {
        int sum = 0;
        for (int j = 0; j < COURSES; j++) {
            sum += students[i].scores[j];
        }
        students[i].average = (short)(sum / COURSES);
    }
}

// 高精度计时函数
double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

int main() {
    struct student *students = malloc(N * sizeof(struct student));
    if (students == NULL) {
        printf("内存分配失败!\n");
        return 1;
    }
    
    srand(time(NULL));
    
    printf("=== 高性能测试 - 计算平均成绩 ===\n");
    printf("学生数量: %d, 预热: %d次, 测试: %d次\n\n", N, WARMUP, ITERATIONS);
    
    // 初始化学生数据
    for (int i = 0; i < N; i++) {
        if (i == 0) {
            strcpy(students[i].name, "YourName");
            strcpy(students[i].sid, "U202414649");
        } else {
            snprintf(students[i].name, 8, "Stu%04d", i);
            snprintf(students[i].sid, 12, "U2024%05d", i);
        }
        
        for (int j = 0; j < COURSES; j++) {
            students[i].scores[j] = (short)(50 + rand() % 50);
        }
        students[i].average = 0;
    }
    
    // 预热运行（避免冷启动影响）
    printf("预热运行...\n");
    for (int i = 0; i < WARMUP; i++) {
        for (int j = 0; j < N; j++) {
            students[j].average = 0;
        }
        calculate_averages_c(students, N);
    }
    
    // 测试C版本
    printf("测试C版本...\n");
    double start = get_time();
    for (int i = 0; i < ITERATIONS; i++) {
        for (int j = 0; j < N; j++) {
            students[j].average = 0;
        }
        calculate_averages_c(students, N);
    }
    double end = get_time();
    double time_c = (end - start) / ITERATIONS;
    
    // 测试汇编版本
    printf("测试基础汇编版本...\n");
    start = get_time();
    for (int i = 0; i < ITERATIONS; i++) {
        for (int j = 0; j < N; j++) {
            students[j].average = 0;
        }
        calculate_averages_asm(students, N);
    }
    end = get_time();
    double time_asm = (end - start) / ITERATIONS;
    
    // 测试优化版本1
    printf("测试优化汇编版本1...\n");
    start = get_time();
    for (int i = 0; i < ITERATIONS; i++) {
        for (int j = 0; j < N; j++) {
            students[j].average = 0;
        }
        calculate_averages_asm_opt1(students, N);
    }
    end = get_time();
    double time_opt1 = (end - start) / ITERATIONS;
    
    // 测试优化版本2
    printf("测试优化汇编版本2...\n");
    start = get_time();
    for (int i = 0; i < ITERATIONS; i++) {
        for (int j = 0; j < N; j++) {
            students[j].average = 0;
        }
        calculate_averages_asm_opt2(students, N);
    }
    end = get_time();
    double time_opt2 = (end - start) / ITERATIONS;
    
    printf("\n=== 性能测试结果 ===\n");
    printf("C版本:        %.6f秒/次\n", time_c);
    printf("基础汇编版本: %.6f秒/次 (加速比: %.2fx)\n", time_asm, time_c/time_asm);
    printf("优化版本1:    %.6f秒/次 (加速比: %.2fx)\n", time_opt1, time_c/time_opt1);
    printf("优化版本2:    %.6f秒/次 (加速比: %.2fx)\n", time_opt2, time_c/time_opt2);
    
    free(students);
    return 0;
}