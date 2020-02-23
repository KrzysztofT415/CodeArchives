# Makefile
all: main clean
main: main.o phi.o
	clang -lm -o 3 main.o phi.o
main.o: main.c
	clang -c main.c
phi.o: phi.c
	clang -c phi.c
clean:
	rm -f *.o
