#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "gol.h"

#define TRUE    1
#define FALSE   0

/* gameoflife.c: a program to test the library
 * this is also where we do the command-line switch magic */

int main(int argc, char **argv)
{
    int sflag = FALSE;      /* Bools for 's' and 't' */
    int tflag = FALSE;
    char *ivalue = NULL;    /* "strings" for i, o, g */
    char *ovalue = NULL;
    char *gvalue = NULL;  
    int c = 0;              /* store current argument during scanning */
    opterr = 0;

    while ((c=getopt(argc, argv, "i:o:g:st")) != -1) {
        switch(c) {
            case 's':
                sflag = TRUE;
                break;
            case 't':
                tflag = TRUE;
                break;
            case 'i':
                ivalue = optarg;
                break;
            case 'o':
                ovalue = optarg;
                break;
            case 'g':
                gvalue = optarg;
                break;
            case '?':
                printf("Unknown option %c. Exiting.\n", optopt);
        }
    }
    printf("sflag set to %d\n", sflag);
    printf("tflag set to %d\n", tflag);
    printf("Input file: %s\n", ivalue);
    printf("Output file: %s\n", ovalue);
    printf("Number of generations: %s\n", gvalue);

    FILE *infile;
    if (ivalue != NULL) {
        if ((infile = fopen(ivalue, "r")) == NULL) {
            printf("Can't open input file. Exiting.\n");
            exit (1);
        }
    } else {
        infile = stdin;
    }
    FILE *outfile;
    if (ovalue != NULL) {
        if ((outfile = fopen(ovalue, "r")) == NULL) {
            printf("Can't open output file. Exiting.\n");
            exit (1);
        }
    } else {
        outfile = stdout;
    }


    struct universe v; 
    read_in_file(infile, &v);
    write_out_file(stdout, &v);
    /*is_alive(&v, 1, 2);*/
    /*printf("%d\n",will_be_alive(&v, 2, 5));
    printf("%d\n",will_be_alive(&v, 4, 5));
    printf("%d\n",will_be_alive(&v, 3, 6));
    printf("%d\n",will_be_alive(&v, 4, 6));
    printf("%d\n",will_be_alive(&v, 3, 7));
    evolve(&v, will_be_alive);
    write_out_file(stdout, &v); 
    evolve(&v, will_be_alive);
    write_out_file(stdout, &v); 
    evolve(&v, will_be_alive);
    write_out_file(stdout, &v); 
    evolve(&v, will_be_alive);
    write_out_file(stdout, &v);*/ 
    evolve(&v, will_be_alive_torus);
    putchar('\n');
    write_out_file(stdout, &v); 
    evolve(&v, will_be_alive_torus);
    putchar('\n');
    write_out_file(stdout, &v);    print_statistics(&v);
    return 0;
}
