OPT = -O2

build:
	gcc -o main $(OPT) main.c
	./main

asm:
	gcc -S -masm=intel $(OPT) -fverbose-asm main.c -o asm.s
