all: assert option ex_option

assert: assert.c assert.h
	gcc -c assert.c -o assert.o

option: option.c option.h assert.o
	gcc -c option.c -o option.o assert.o

ex_option: ex_option.c option.o assert.o
	gcc -o ex_option ex_option.c option.o assert.o

clean:
	rm *.o
