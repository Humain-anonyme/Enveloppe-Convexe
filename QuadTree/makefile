

CC=gcc
LDLIBS=-lm -lMLV
CFLAGS=-std=c17 -pedantic -Wall
OBJ=main.o QuadTree.o interface.o 


quad: $(OBJ)
	$(CC) -o $@ $^ $(LDLIBS)


QuadTree.o: QuadTree.c

interface.o: interface.c  




%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o
