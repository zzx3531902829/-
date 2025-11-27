CC = gcc
ASM = nasm
CFLAGS_DEBUG = -g -O0
CFLAGS_RELEASE = -O3 -march=native
ASMFLAGS = -f elf64

all: debug release

debug:
	$(ASM) $(ASMFLAGS) asm_functions.asm -o asm_functions_debug.o
	$(CC) $(CFLAGS_DEBUG) main.c asm_functions_debug.o -o student_debug -no-pie

release:
	$(ASM) $(ASMFLAGS) asm_functions.asm -o asm_functions_release.o
	$(CC) $(CFLAGS_RELEASE) main.c asm_functions_release.o -o student_release -no-pie

clean:
	rm -f *.o student_debug student_release

.PHONY: all debug release clean