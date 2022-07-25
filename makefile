all: assert str dyn wrapper main clean

assert: assert.c assert.h
	gcc -c assert.c -o assert.o

wrapper: wrapper.c wrapper.h assert.o
	gcc -c wrapper.c -o wrapper.o assert.o

str: str.c str.h assert.o
	gcc -c str.c -o str.o assert.o

dyn: dyn.c dyn.h str.h
	gcc -c dyn.c -o dyn.o assert.o str.o

main: main.c assert.o dyn.o wrapper.o
	gcc -o main main.c assert.o dyn.o wrapper.o

clean:
	rm *.o
