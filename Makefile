all: assembler

assembler: assembler.o parser.o
	gcc -o assembler assembler.o parser.o

assembler.o: assembler.c parser.h
	gcc -c assembler.c

parser.o: parser.c parser.h
	gcc -c parser.c

clean: 
	rm -rf *.o assembler
