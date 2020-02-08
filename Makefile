all: gameoflife.o gol.h
	gcc -fPIC -Wall -Wextra -pedantic -std=c11 -c gameoflife.c -o gameoflife.o
	gcc -Wall -Wextra -pedantic -std=c11 -o gameoflife

gameoflife.o: gameoflife.c gol.h
	gcc -Wall -Wextra -pedantic -std=c11 -c gameoflife.c

clean:
	rm -rf gameoflife libgol.so

all: gameoflife.c gol.h gol.c
	gcc -Wall -Wextra -pedantic -std=c11 -o gameoflife gol.o
