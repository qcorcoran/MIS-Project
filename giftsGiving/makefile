##Quinn Corcoran
##

##FILE: Makefile giftsGiving

##

CC = g++
CFLAGS = -c -g -Wall 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

all: main.o tree.o bruteForce.o verify.o inputMaker.o inputMaker16382.o inputMaker131070.o inputMaker10101.o inputMaker524286.o inputMaker878906.o inputMaker983038.o
	$(CC) -o giftsGiving main.o tree.o
	$(CC) -o bruteForce bruteForce.o tree.o
	$(CC) -o verify verify.o
	$(CC) -o inputMaker inputMaker.o
	$(CC) -o inputMaker16382 inputMaker16382.o
	$(CC) -o inputMaker131070 inputMaker131070.o
	$(CC) -o inputMaker10101 inputMaker10101.o
	$(CC) -o inputMaker524286 inputMaker524286.o
	$(CC) -o inputMaker878906 inputMaker878906.o
	$(CC) -o inputMaker983038 inputMaker983038.o

giftsGiving: main.o tree.o
	$(CC) -o giftsGiving main.o tree.o

main.o: main.cpp

tree.o: tree.cpp

bruteForce: bruteForce.o tree.o
	$(CC) -o bruteForce bruteForce.o tree.o

verify: verify.o
	$(CC) -o verify verify.o

verify.o: verify.cpp

inputMakers: inputMaker.o inputMaker16382.o inputMaker131070.o inputMaker10101.o inputMaker524286.o inputMaker878906.o inputMaker983038.o
	$(CC) -o inputMaker inputMaker.o
	$(CC) -o inputMaker16382 inputMaker16382.o
	$(CC) -o inputMaker131070 inputMaker131070.o
	$(CC) -o inputMaker10101 inputMaker10101.o
	$(CC) -o inputMaker524286 inputMaker524286.o
	$(CC) -o inputMaker878906 inputMaker878906.o
	$(CC) -o inputMaker983038 inputMaker983038.o

inputMaker: inputMaker.o
	$(CC) -o inputMaker inputMaker.o

inputMaker.o: inputMaker.cpp

inputMaker16382: inputMaker16382.o
	$(CC) -o inputMaker16382 inputMaker16382.o

inputMaker16382.o: inputMaker16382.cpp

inputMaker131070: inputMaker131070.o
	$(CC) -o inputMaker131070 inputMaker131070.o

inputMaker131070.o: inputMaker131070.cpp

inputMaker10101: inputMaker10101.o
	$(CC) -o inputMaker10101 inputMaker10101.o

inputMaker10101.o: inputMaker10101.cpp

inputMaker524286: inputMaker524286.o
	$(CC) -o inputMaker524286 inputMaker524286.o

inputMaker524286.o: inputMaker524286.cpp

inputMaker878906: inputMaker878906.o
	$(CC) -o inputMaker878906 inputMaker878906.o

inputMaker878906.o: inputMaker878906.cpp

inputMaker983038: inputMaker983038.o
	$(CC) -o inputMaker983038 inputMaker983038.o

inputMaker983038.o: inputMaker983038.cpp

clean:
	rm -f *.o giftsGiving bruteForce verify inputMaker inputMaker16382 inputMaker131070 inputMaker10101 inputMaker524286 inputMaker878906 inputMaker983038
