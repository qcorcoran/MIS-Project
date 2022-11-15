##Quinn Corcoran
##

##FILE: Makefile permutation

##

CC = g++
CFLAGS = -c -g -Wall 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

all: main.o permutationGraph.o splayTree.o inputMaker.o verify.o
	$(CC) -o permutation main.o permutationGraph.o splayTree.o
	$(CC) -o inputMaker inputMaker.o
	$(CC) -o verify verify.o

permutation: main.o permutationGraph.o splayTree.o
	$(CC) -o trapezoidShooting main.o permutationGraph.o splayTree.o

main.o: main.cpp

permutationGraph.o: permutationGraph.cpp

splayTree.o: splayTree.cpp

inputMaker: inputMaker.o
	$(CC) -o inputMaker inputMaker.o

inputMaker.o: inputMaker.cpp

verify: verify.o
	$(CC) -o verify verify.o

verify.o: verify.cpp

clean:
	rm -f *.o permutation inputMaker verify
