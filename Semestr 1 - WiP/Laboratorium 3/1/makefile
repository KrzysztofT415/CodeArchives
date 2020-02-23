# Makefile
all: main clean
main: napis.o main.o
	clang -o 1 main.o napis.o
napis.o: napis.c
	clang -c napis.c
main.o: main.c
	clang -c main.c
clean:
	rm -f *.o
