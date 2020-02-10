CFLAGS=-Wall -Wextra -pedantic -std=c11

all: gameoflife.c gol.h gol.c
	gcc $(CFLAGS) -fPIC -c gameoflife.c -o gameoflife.o
	gcc $(CFLAGS) -fPIC -c gol.c -o gol.o
	gcc $(CFLAGS) -shared gol.o -o libgol.so
	gcc $(CFLAGS) gameoflife.o -L. -lgol -lm -o gameoflife

gameoflife.o: gameoflife.c gol.h
	gcc $(CFLAGS) -fPIC -c gameoflife.c -o gameoflife.o

gol.o: gol.h gol.c
	gcc $(CFLAGS) -fPIC -c gol.c -o gol.o

libgol.so: gol.o
	gcc $(CFLAGS) -shared gol.o -o libgol.so

gameoflife: gameoflife.o
	gcc $(CFLAGS) gameoflife.o -L. -lgol -lm -o gameoflife

clean:
	rm -rf gameoflife libgol.so gameoflife.o gol.o
