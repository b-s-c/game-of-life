#include <stdio.h>
#include "gol.h"

/* gameoflife.c: a program to test the library */

/*int main(int argc, char argv[])*/
int main()
{
    struct universe v; 
    read_in_file(stdin, &v);
    /*evolve(&v, will_be_alive);
    evolve(&v, will_be_alive);
    evolve(&v, will_be_alive);
    evolve(&v, will_be_alive);
    evolve(&v, will_be_alive);
    write_out_file(stdout, &v);*/
    return 0;

    /* if input file NOT supplied~ */
    int c = 0;
    int num_cells = 0;
    while ((c=getchar())!=EOF) {
        if (c == '.' || c == '\n') {
            continue;
        } else if (c == '*') {
            /* append x and y values to array in struct */
        } else {
            printf("The input contains invalid character '%c'.\n", c);
            return -1;
        }
        num_cells += 1;
    }
}
