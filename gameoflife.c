#include <stdio.h>
#include <stdlib.h>
#include "gol.h"

/* gameoflife.c: a program to test the library
 * this is also where we do the command-line switch magic */

/*int main(int argc, char argv[])*/
int main()
{
    FILE *infile;
    if ((infile = fopen("glider.txt", "r")) == NULL) {
        printf("Can't open file\n");
        exit (1);
    }
    struct universe v; 
    read_in_file(infile, &v);
    write_out_file(stdout, &v);
    is_alive(&v, 1, 2);
    /*printf("%d\n",will_be_alive(&v, 2, 5));
    printf("%d\n",will_be_alive(&v, 4, 5));
    printf("%d\n",will_be_alive(&v, 3, 6));
    printf("%d\n",will_be_alive(&v, 4, 6));
    printf("%d\n",will_be_alive(&v, 3, 7));*/
    evolve(&v, will_be_alive);
    write_out_file(stdout, &v); 
    evolve(&v, will_be_alive);
    write_out_file(stdout, &v); 
    evolve(&v, will_be_alive);
    write_out_file(stdout, &v); 
    evolve(&v, will_be_alive);
    write_out_file(stdout, &v); 
    evolve(&v, will_be_alive);
    putchar('\n');
    write_out_file(stdout, &v); 
    print_statistics(&v);
    return 0;
}
