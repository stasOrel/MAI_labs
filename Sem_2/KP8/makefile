all: prog

prog: circular_list.h circular_list.o main.o
	gcc main.o circular_list.o -o prog

main.o: main.c
	gcc -c main.c

circular_list.o: circular_list.c
	gcc -c circular_list.c

clean:
	rm *.o