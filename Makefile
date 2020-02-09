all: gameoflife.c gol.h gol.c
	gcc gol.c gol.h gameoflife.c -Wall -Wextra -pedantic -std=c11 -o gameoflife

gameoflife.o: gameoflife.c gol.h
	gcc -Wall -Wextra -pedantic -std=c11 -c gameoflife.c

clean:
	rm -rf gameoflife libgol.so


