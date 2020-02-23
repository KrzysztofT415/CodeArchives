# Makefile
all: main clean
main: main.o north.o south.o west.o east.o newagent.o distance.o
	clang -lm -o 4 main.o north.o south.o west.o east.o newagent.o distance.o
main.o: main.c
	clang -c main.c
north.o: north.c
	clang -c north.c
south.o: south.c
	clang -c south.c
west.o: west.c
	clang -c west.c
east.o: east.c
	clang -c east.c
newagent.o: newagent.c
	clang -c newagent.c
distance.o: distance.c
	clang -c distance.c
clean:
	rm -f *.o
