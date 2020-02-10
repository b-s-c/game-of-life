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
    int iflag = FALSE;      /* used to determine whether or not to write a newline before output (purely for keeping the program output neat) */
    char *ivalue = NULL;    /* "strings" for i, o, g */
    char *ovalue = NULL;
    char *gvalue = NULL;  
    int c = 0;              /* store current argument during scanning with getopt */
    opterr = 0;             /* ensure zero value, and therefore getopt will exhibit default behaviour */

    /* parse arguments */
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
                iflag = TRUE;
                break;
            case 'o':
                ovalue = optarg;
                break;
            case 'g':
                gvalue = optarg;
                break;
            case '?':
                if (optopt == 'g' || optopt == 'i' || optopt == 'o') {
                    printf("The option %c requires a corresponding argument. Exiting.\n", optopt);
                    exit(1);
                }
                printf("Unknown option %c. Exiting.\n", optopt);
                exit(1);
            default:
                exit(1);
        }
    }

    FILE *outfile;
    if (ovalue != NULL) {
        if ((outfile = fopen(ovalue, "r")) == NULL) {
            printf("Can't open output file (does it exist?). Exiting.\n");
            exit (1);
        }
    } else {
        outfile = stdout;
    }

    FILE *infile;
    if (ivalue != NULL) {
        if ((infile = fopen(ivalue, "r")) == NULL) {
            printf("Can't open input file (does it exist?). Exiting.\n");
            exit (1);
        }
    } else {
        infile = stdin;
    }

    int gen = 0;    /* bit of memory to store the integer value of no. generations */
    if (gvalue == NULL) {
        gen = 5;
    } else if (gvalue != NULL) {
        if ((gen = atoi(gvalue)) == 0) {
            printf("Invalid parameter passed through -g (is it a number?). Exiting.\n");
            exit (1);
        }
    }

    /* for debugging
    printf("sflag set to %d\n", sflag);
    printf("tflag set to %d\n", tflag);
    printf("Input file: %s\n", ivalue);
    printf("Output file: %s\n", ovalue);
    printf("Number of generations: %d\n", gen);
    */

    /* initialise a universe */
    struct universe v;

    /* read input */
    read_in_file(infile, &v);

    /* evolve the given number of times with the given rule */
    while (gen > 0) {
        if (!tflag) {
            evolve(&v, will_be_alive);
        } else if (tflag) {
            evolve(&v, will_be_alive_torus);
        } else {
            printf("tflag corrupted. Exiting.\n");
            exit (1);
        }
        gen--;
    }

    /* write output */
    if (!iflag) {
        putchar('\n');
    }
    write_out_file(outfile, &v);

    /* print stats after final generation, if required */
    if (sflag) {
        print_statistics(&v);
    }

    /* success!~ */
    return 0;
}
