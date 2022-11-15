##Quinn Corcoran
##

##FILE: Makefile relaxedScheduling

##

CC = g++
CFLAGS = -c -g -Wall 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

all: main.o intervalGraph.o inputMaker.o verify.o
	$(CC) -o relaxedScheduling main.o intervalGraph.o
	$(CC) -o inputMaker inputMaker.o
	$(CC) -o verify verify.o

relaxedScheduling: main.o intervalGraph.o
	$(CC) -o relaxedScheduling main.o intervalGraph.o

main.o: main.cpp

intervalGraph.o: intervalGraph.cpp

inputMaker: inputMaker.o
	$(CC) -o inputMaker inputMaker.o

inputMaker.o: inputMaker.cpp

verify: verify.o
	$(CC) -o verify verify.o

verify.o: verify.cpp

clean:
	rm -f *.o relaxedScheduling inputMaker verify
