##Quinn Corcoran
##

##FILE: Makefile circularArc

##

CC = g++
CFLAGS = -c -g -Wall 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

all: main.o graph.o verify.o
	$(CC) -o circularArc main.o graph.o
	$(CC) -o verify verify.o

circularArc: main.o graph.o
	$(CC) -o circularArc main.o graph.o

main.o: main.cpp

graph.o: graph.cpp

verify: verify.o
	$(CC) -o verify verify.o

verify.o: verify.cpp

clean:
	rm -f *.o circularArc verify
