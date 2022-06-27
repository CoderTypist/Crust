all: assert dyn option ex_option clean

assert: assert.c assert.h
	gcc -c assert.c -o assert.o

dyn: dyn.c dyn.c str.h
	gcc -c dyn.c -o dyn.o

option: option.c option.h assert.o
	gcc -c option.c -o option.o assert.o

ex_option: ex_option.c assert.o dyn.o option.o
	gcc -o ex_option ex_option.c assert.o dyn.o option.o

clean:
	rm *.o
