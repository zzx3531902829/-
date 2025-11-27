#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 100
#define COURSES 8

struct student {
    char name[8];
    char sid[11];
    short scores[COURSES];
    short average;
};

// 函数声明
void calculate_averages(struct student *students, int count);
void sort_students(struct student *students, int count);
void print_students(struct student *students, int count);

int main() {
    struct student students[N];
    
    // 初始化第0个学生（自己）
    strcpy(students[0].name, "YourName");
    strcpy(students[0].sid, "U202315123");
    for (int i = 0; i < COURSES; i++) {
        students[0].scores[i] = (short)(80 + rand() % 20);
    }
    
    // 初始化其他学生
    for (int i = 1; i < N; i++) {
        snprintf(students[i].name, 8, "Stu%03d", i);
        snprintf(students[i].sid, 11, "U2023%06d", i);
        for (int j = 0; j < COURSES; j++) {
            students[i].scores[j] = (short)(50 + rand() % 50);
        }
    }
    
    printf("排序前学生信息:\n");
    print_students(students, N);
    
    // 计算平均成绩并计时
    clock_t start = clock();
    calculate_averages(students, N);
    clock_t end = clock();
    double calc_time = (double)(end - start) / CLOCKS_PER_SEC;
    
    // 排序并计时
    start = clock();
    sort_students(students, N);
    end = clock();
    double sort_time = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n排序后学生信息:\n");
    print_students(students, N);
    
    printf("\n计算平均成绩耗时: %.6f秒\n", calc_time);
    printf("排序耗时: %.6f秒\n", sort_time);
    
    return 0;
}

// 计算平均成绩
void calculate_averages(struct student *students, int count) {
    for (int i = 0; i < count; i++) {
        int sum = 0;
        for (int j = 0; j < COURSES; j++) {
            sum += students[i].scores[j];
        }
        students[i].average = (short)(sum / COURSES);
    }
}

// 冒泡排序
void sort_students(struct student *students, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].average < students[j+1].average) {
                struct student temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }
}

// 打印学生信息
void print_students(struct student *students, int count) {
    for (int i = 0; i < count; i++) {
        printf("%-8s %-11s ", students[i].name, students[i].sid);
        for (int j = 0; j < COURSES; j++) {
            printf("%3d ", students[i].scores[j]);
        }
        printf("| Avg: %3d\n", students[i].average);
    }
}