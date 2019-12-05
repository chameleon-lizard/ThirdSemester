all: file
file: file.o
	gcc -o 4_fourth 4_fourth.o
file.o: 4_fourth.c 
	gcc -std=c99 -c -o 4_fourth.o 4_fourth.c
clean: 
	rm -f *.o
