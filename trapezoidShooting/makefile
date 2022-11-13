##Quinn Corcoran
##

##FILE: Makefile trapezoidShooting

##

CC = g++
CFLAGS = -c -g -Wall 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

all: main.o graph.o splayTree.o inputMaker.o verify.o
	$(CC) -o trapezoidShooting main.o graph.o splayTree.o
	$(CC) -o inputMaker inputMaker.o
	$(CC) -o verify verify.o

trapezoidShooting: main.o graph.o splayTree.o
	$(CC) -o trapezoidShooting main.o graph.o splayTree.o

main.o: main.cpp

graph.o: graph.cpp

splayTree.o: splayTree.cpp

inputMaker: inputMaker.o
	$(CC) -o inputMaker inputMaker.o

inputMaker.o: inputMaker.cpp

verify: verify.o
	$(CC) -o verify verify.o

verify.o: verify.cpp

clean:
	rm -f *.o trapezoidShooting inputMaker verify
