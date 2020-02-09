#include <stdio.h>
#include "gol.h"

/* gameoflife.c: a program to test the library */

/*int main(int argc, char argv[])*/
int main()
{
    struct universe v; 
    read_in_file(stdin, &v);
 /* evolve(&v, will_be_alive);
    evolve(&v, will_be_alive);
    evolve(&v, will_be_alive);
    evolve(&v, will_be_alive);
    evolve(&v, will_be_alive);
    write_out_file(stdout, &v); */
    return 0;
}
