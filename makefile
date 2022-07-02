all: assert dyn wrapper main clean

assert: assert.c assert.h
	gcc -c assert.c -o assert.o

dyn: dyn.c dyn.c str.h
	gcc -c dyn.c -o dyn.o

wrapper: wrapper.c wrapper.h assert.o
	gcc -c wrapper.c -o wrapper.o assert.o

main: main.c assert.o dyn.o wrapper.o
	gcc -o main main.c assert.o dyn.o wrapper.o

clean:
	rm *.o
