all: assert option main

assert: assert.c assert.h
	gcc -c assert.c -o assert.o

option: option.c option.h assert.o
	gcc -c option.c -o option.o assert.o

main: main.c option.o assert.o
	gcc -o main main.c option.o assert.o
