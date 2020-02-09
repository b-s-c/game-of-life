#include <stdio.h>
#include "gol.h"

/* gameoflife.c: a program to test the library
 * this is also where we do the command-line switch magic */

/*int main(int argc, char argv[])*/
int main()
{
    struct universe v; 
    read_in_file(stdin, &v);
    is_alive(&v, 1, 2);
 /* evolve(&v, will_be_alive);
    evolve(&v, will_be_alive);
    evolve(&v, will_be_alive);
    evolve(&v, will_be_alive);
    evolve(&v, will_be_alive);
    write_out_file(stdout, &v); */
    return 0;
}
