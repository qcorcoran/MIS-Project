##Quinn Corcoran
##

##FILE: Makefile circularArc

##

CC = g++
CFLAGS = -c -g -Wall 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

all: main.o circularArcGraph.o verify.o
	$(CC) -o circularArc main.o circularArcGraph.o
	$(CC) -o verify verify.o

circularArc: main.o circularArcGraph.o
	$(CC) -o circularArc main.o circularArcGraph.o

main.o: main.cpp

circularArcGraph.o: circularArcGraph.cpp

verify: verify.o
	$(CC) -o verify verify.o

verify.o: verify.cpp

clean:
	rm -f *.o circularArc verify
