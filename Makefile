
CC=gcc
CFLAGS= -Wall -std=c99 -O3

aedmaps: main.o modos.o adjacencylist.o Dijkstra.o heap.o BFS.o
	$(CC) $(CFLAGS) -o aedmaps main.o modos.o adjacencylist.o Dijkstra.o heap.o BFS.o

main.o: main.c modos.h adjacencylist.h structs.h 
	$(CC) -c $(CFLAGS) main.c

modos.o: modos.c structs.h adjacencylist.h Dijkstra.h BFS.h
	$(CC) -c $(CFLAGS) modos.c

Dijkstra.o: Dijkstra.c Dijkstra.h adjacencylist.h heap.h structs.h 
	$(CC) -c $(CFLAGS) Dijkstra.c

heap.o: heap.c heap.h adjacencylist.h structs.h 
	$(CC) -c $(CFLAGS) heap.c

adjacencylist.o: adjacencylist.c adjacencylist.h structs.h 
	$(CC) -c $(CFLAGS) adjacencylist.c

BFS.o: BFS.c BFS.h structs.h
	$(CC) -c $(CFLAGS) BFS.c

clean::
	rm -f *.o core a.out aedmaps *~





VALG = valgrind --leak-check=full