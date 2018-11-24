all: main

main: main.o assembler.o
	gcc -o main main.o assembler.o

main.o: main.c assembler.h
	gcc -c main.c

somma.o: assembler.c assembler.h
	gcc -c assembler.c

clean: 
	rm -rf *.o main
