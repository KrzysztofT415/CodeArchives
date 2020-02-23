# Makefile
all: main clean
main: main.o f.o rozwiazanie.o
	clang -lm -o 2 main.o f.o rozwiazanie.o
main.o: main.c
	clang -c main.c
f.o: f.c
	clang -c f.c
rozwiazanie.o: rozwiazanie.c
	clang -c rozwiazanie.c
clean:
	rm -f *.o
