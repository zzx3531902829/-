#include <stdio.h>
#include <limits.h>

// 函数声明
int test_isEqual(int x, int y);
int test_bitOr(int x, int y);
int test_sign(int x);
int test_upperBits(int n);
int test_replaceByte(int x, int n, int c);
int test_allOddBits(int x);
int test_bitMask(int highbit, int lowbit);
int test_addOK(int x, int y);
int test_rotateLeft(int x, int n);
int test_bitCount(int x);

// (1) 判断x和y是否相等
int isEqual(int x, int y) {
    return !(x ^ y);
}

// (2) 对x和y进行按位或运算
int bitOr(int x, int y) {
    return ~(~x & ~y);
}

// (3) 获取x的符号
int sign(int x) {
    return ((x >> 31) & ~1) | (!!x);
}

// (4) 获取高n位设为1的整数
int upperBits(int n) {
    return ((!!n) << 31) >> (n + (~0));
}

// (5) 将x的第n个字节替换为c
int replaceByte(int x, int n, int c) {
    int mask = 0xFF << (n << 3);
    return (x & ~mask) | ((c & 0xFF) << (n << 3));
}

// (6) 检查所有奇数位是否都设为1
int allOddBits(int x) {
    int mask = 0xAA;
    mask = mask | (mask << 8);
    mask = mask | (mask << 16);
    return !((x & mask) ^ mask);
}

// (7) 生成从lowbit到highbit位设为1的数
int bitMask(int highbit, int lowbit) {
    // 创建从0到highbit位设为1的掩码
    int high_mask = (1 << (highbit + 1)) + ~0;
    // 创建从0到lowbit-1位设为1的掩码
    int low_mask = (1 << lowbit) + ~0;
    // 通过异或操作获取从lowbit到highbit的位
    return high_mask & ~low_mask;
}

// (8) 检查x+y是否会导致溢出
int addOK(int x, int y) {
    int sum = x + y;
    int sign_x = x >> 31;
    int sign_y = y >> 31;
    int sign_sum = sum >> 31;
    return !!(~(sign_x ^ sign_y) & (sign_x ^ sign_sum));
}

// (9) 将x循环左移n位
int rotateLeft(int x, int n) {
    int mask = ~0;
    int shift = n & 0x1F;  // 确保n在0-31范围内
    return (x << shift) | ((x >> (32 + (~shift + 1))) & ~(mask << shift));
}

// (10) 计算x中1的位数
int bitCount(int x) {
    // 使用分治法统计1的位数
    int mask1 = 0x55555555;  // 0101...
    int mask2 = 0x33333333;  // 0011...
    int mask3 = 0x0F0F0F0F;  // 00001111...
    int mask4 = 0x00FF00FF;  // 0000000011111111...
    int mask5 = 0x0000FFFF;  // 00000000000000001111111111111111
    
    x = (x & mask1) + ((x >> 1) & mask1);
    x = (x & mask2) + ((x >> 2) & mask2);
    x = (x & mask3) + ((x >> 4) & mask3);
    x = (x & mask4) + ((x >> 8) & mask4);
    x = (x & mask5) + ((x >> 16) & mask5);
    
    return x;
}

// 测试函数实现
int test_isEqual(int x, int y) { return x == y; }

int test_bitOr(int x, int y) { return x | y; }

int test_sign(int x) {
    if (x == 0) return 0;
    return (x > 0) ? 1 : -1;
}

int test_upperBits(int n) {
    if (n <= 0) return 0;
    if (n >= 32) return ~0;
    return (~0) << (32 - n);
}

int test_replaceByte(int x, int n, int c) {
    unsigned char *bytes = (unsigned char *)&x;
    bytes[n & 0x3] = (unsigned char)(c & 0xFF);
    return x;
}

int test_allOddBits(int x) {
    for (int i = 1; i < 32; i += 2) {
        if (!((x >> i) & 1)) return 0;
    }
    return 1;
}

int test_bitMask(int highbit, int lowbit) {
    if (lowbit > highbit) return 0;
    int mask = 0;
    for (int i = lowbit; i <= highbit; i++) {
        mask |= (1 << i);
    }
    return mask;
}

int test_addOK(int x, int y) {
    long long sum = (long long)x + y;
    return (sum > INT_MAX || sum < INT_MIN) ? 1 : 0;
}

int test_rotateLeft(int x, int n) {
    n = n % 32;
    if (n == 0) return x;
    return (x << n) | ((unsigned)x >> (32 - n));
}

int test_bitCount(int x) {
    int count = 0;
    for (int i = 0; i < 32; i++) {
        if (x & (1 << i)) count++;
    }
    return count;
}

// 测试函数
void test_function(int test_num, const char* name, int (*func)(), int (*test_func)(), int* args, int arg_count) {
    int result = 0, expected = 0;
    
    switch(arg_count) {
        case 1:
            result = func(args[0]);
            expected = test_func(args[0]);
            break;
        case 2:
            result = func(args[0], args[1]);
            expected = test_func(args[0], args[1]);
            break;
        case 3:
            result = func(args[0], args[1], args[2]);
            expected = test_func(args[0], args[1], args[2]);
            break;
    }
    
    printf("测试 %d (%s): ", test_num, name);
    if (result == expected) {
        printf("正确 (结果: %d, 期望: %d)\n", result, expected);
    } else {
        printf("错误 (结果: %d, 期望: %d)\n", result, expected);
    }
}

int main() {
    printf("位操作函数测试结果:\n\n");
    
    // 测试isEqual
    int args1[] = {5, 5};
    test_function(1, "isEqual", (int(*)())isEqual, (int(*)())test_isEqual, args1, 2);
    
    int args2[] = {4, 5};
    test_function(1, "isEqual", (int(*)())isEqual, (int(*)())test_isEqual, args2, 2);
    
    // 测试bitOr
    int args3[] = {0x1234, 0x5678};
    test_function(2, "bitOr", (int(*)())bitOr, (int(*)())test_bitOr, args3, 2);
    
    // 测试sign
    int args4[] = {130};
    test_function(3, "sign", (int(*)())sign, (int(*)())test_sign, args4, 1);
    
    int args5[] = {-23};
    test_function(3, "sign", (int(*)())sign, (int(*)())test_sign, args5, 1);
    
    // 测试upperBits
    int args6[] = {4};
    test_function(4, "upperBits", (int(*)())upperBits, (int(*)())test_upperBits, args6, 1);
    
    // 测试replaceByte
    int args7[] = {0x12345678, 1, 0xab};
    test_function(5, "replaceByte", (int(*)())replaceByte, (int(*)())test_replaceByte, args7, 3);
    
    // 测试allOddBits
    int args8[] = {0xFFFFFFFD};
    test_function(6, "allOddBits", (int(*)())allOddBits, (int(*)())test_allOddBits, args8, 1);
    
    int args9[] = {0xAAAAAAAA};
    test_function(6, "allOddBits", (int(*)())allOddBits, (int(*)())test_allOddBits, args9, 1);
    
    // 测试bitMask
    int args10[] = {5, 3};
    test_function(7, "bitMask", (int(*)())bitMask, (int(*)())test_bitMask, args10, 2);
    
    // 测试addOK
    int args11[] = {0x80000000, 0x80000000};
    test_function(8, "addOK", (int(*)())addOK, (int(*)())test_addOK, args11, 2);
    
    // 测试rotateLeft
    int args12[] = {0x87654321, 4};
    test_function(9, "rotateLeft", (int(*)())rotateLeft, (int(*)())test_rotateLeft, args12, 2);
    
    // 测试bitCount
    int args13[] = {5};
    test_function(10, "bitCount", (int(*)())bitCount, (int(*)())test_bitCount, args13, 1);
    
    int args14[] = {7};
    test_function(10, "bitCount", (int(*)())bitCount, (int(*)())test_bitCount, args14, 1);
    
    return 0;
}