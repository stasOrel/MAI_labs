all: prog

prog: matrix.h matrix.o main.o
	gcc main.o matrix.o -o prog

main.o: main.c
	gcc -c main.c

matrix.o: matrix.c
	gcc -c matrix.c

clean:
	rm *.o