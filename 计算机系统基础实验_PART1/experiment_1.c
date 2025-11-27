#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define N 5

struct student {
    char name[8];
    short age;
    float score;
    char remark[200];
};

int pack_student_whole(struct student* s, int sno, char *buf);
int pack_student_bytebybyte(struct student* s, int sno, char *buf);
int restore_student(char *buf, int len, struct student* s);

int main() {
    struct student new_s[5];
    char message[1024] = {0};
    
    struct student old_s[5] = {{"", 1, 2, ""},
                       {"zzx", 18, 49, "none"}, 
                       {"zhl", 19, 48, "none"}, 
                       {"zz", 19, 47, "none"}, 
                       {"lj", 20, 30, "none"}
                       };
    
    printf("Enter name for student 0: ");
    fgets(old_s[0].name, 8, stdin);
    printf("\nEnter age for student 0: ");
    scanf("%hd", &old_s[0].age);
    printf("\nEnter score for student 0 (last two digits of student ID): ");
    char c;
    scanf("%f%c", &old_s[0].score, &c);
    printf("\nEnter remark for student 0: ");
    fgets(old_s[0].remark, 200, stdin);
   
    printf("\nData before compression:\n");
    for (int i = 0; i < N; i++) {
        printf("Student %d: Name=%s, Age=%d, Score=%.2f, Remark=%s\n", 
               i, old_s[i].name, old_s[i].age, old_s[i].score, old_s[i].remark);
    }
    
    int total_len = 0;
    total_len += pack_student_whole(old_s, 3, message);
    total_len += pack_student_bytebybyte(old_s + 3, 2, message + total_len);
    
    printf("\nCompressed data length: %d bytes\n", total_len);
    printf("\nFirst 20 bytes of message (hexadecimal):\n");
    for (int i = 0; i < 20; i++) {
        printf("%02X ", (unsigned char)message[i]);
        if ((i+1) % 8 == 0) printf("  ");
    }
    printf("\n");
    
    int restored_count = restore_student(message, total_len, new_s);
    
    printf("\nData after decompression (restored count: %d):\n", restored_count);
    for (int i = 0; i < restored_count; i++) {
        printf("Student %d: Name=%s, Age=%d, Score=%.2f, Remark=%s\n", 
               i, new_s[i].name, new_s[i].age, new_s[i].score, new_s[i].remark);
    }
      
    return 0;
}

int pack_student_whole(struct student* s, int sno, char *buf) {
    int offset = 0;
    
    for (int i = 0; i < sno; i++) {
        strcpy(buf + offset, s[i].name);
        offset += strlen(s[i].name) + 1;
        
        memcpy(buf + offset, &s[i].age, sizeof(short));
        offset += sizeof(short);
        
        memcpy(buf + offset, &s[i].score, sizeof(float));
        offset += sizeof(float);
        
        strcpy(buf + offset, s[i].remark);
        offset += strlen(s[i].remark) + 1;
    }
    return offset;
}

int pack_student_bytebybyte(struct student* s, int sno, char *buf) {
    int offset = 0;
    
    for (int i = 0; i < sno; i++) {
        const char* name_ptr = s[i].name;
        for (int j = 0; j <= strlen(name_ptr); j++) {
            buf[offset++] = name_ptr[j];
        }
        
        char *age_ptr = (char*)&s[i].age;
        buf[offset] = age_ptr[0];
        buf[offset + 1] = age_ptr[1];
        offset += 2;
        
        char *score_ptr = (char*)&s[i].score;
        buf[offset] = score_ptr[0];
        buf[offset + 1] = score_ptr[1];
        buf[offset + 2] = score_ptr[2];
        buf[offset + 3] = score_ptr[3];
        offset += 4;
        
        const char* remark_ptr = s[i].remark;
        for (int j = 0; j <= strlen(remark_ptr); j++) {
            buf[offset++] = remark_ptr[j];
        }
    }
    return offset;
}

int restore_student(char *buf, int len, struct student* s) {
    int offset = 0;
    int count = 0;
    
    for (count = 0; count < N && offset < len; count++) {
        strcpy(s[count].name, buf + offset);
        offset += strlen(buf + offset) + 1;
        
        memcpy(&s[count].age, buf + offset, sizeof(short));
        offset += sizeof(short);
        
        memcpy(&s[count].score, buf + offset, sizeof(float));
        offset += sizeof(float);
        
        strcpy(s[count].remark, buf + offset);
        offset += strlen(buf + offset) + 1;
    }
    
    return count;
}