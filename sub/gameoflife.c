#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gol.h"

#define TRUE    1
#define FALSE   0

/* gameoflife.c: a program to test the library
 * this is also where we do the command-line switch magic */

int main(int argc, char *argv[])
{
    int sflag = FALSE;      /* Bools for 's' and 't' */
    int tflag = FALSE;
    int iinit = FALSE;
    int iflag = FALSE;      /* used to determine whether or not to write a newline before output (purely for keeping the program output neat) */
    int oinit = FALSE;
    int oflag = FALSE;
    int ginit = FALSE;
    int gflag = FALSE;
    char ivalue[50];        /* "strings" storing the parameters for i, o, g */
    char ovalue[50];
    char gvalue[50];  
    char current_arg = '0';
    char arg_param[50];
    int arg_primed = FALSE;
    int gen = 5;

    for (int i = 1; i<argc; i++) {
        if (argv[i][0] == '-') {
            switch(argv[i][1]) {
                case 'i':
                    current_arg = 'i';
                    iinit = TRUE;
                    break;
                case 'o':
                    current_arg = 'o';
                    oinit = TRUE;
                    break;
                case 'g':
                    current_arg = 'g';
                    ginit = TRUE;
                    break;
                case 's':
                    current_arg = 's';
                    sflag = 1;
                    if (argv[i][2] == 't') {
                        tflag = 1;
                    }
                    break;
                case 't':
                    current_arg = 't';
                    tflag = 1;
                    if (argv[i][2] == 's') {
                        sflag = 1;
                    }
                    break;
                default:
                    printf("Invalid parameter passed: %c. Exiting.\n", argv[i][1]);
                    exit(1);
                    break;
            }
        } else {
            strcpy(arg_param, argv[i]); /* unsafe: potential for buffer overflow */
            arg_primed = TRUE;
        }

        if ((current_arg == 'i' || current_arg == 'o' || current_arg == 'g') && arg_primed) {
            switch(current_arg) {
                case 'i':
                    strcpy(ivalue, arg_param);
                    iflag = TRUE;
                    break;
                case 'o':
                    strcpy(ovalue, arg_param);
                    oflag = TRUE;
                    break;
                case 'g':
                    strcpy(gvalue, arg_param);
                    gen = atoi(gvalue);
                    gflag = TRUE;
                    break;
            }
            arg_primed = FALSE;
        }
    }

    FILE *outfile;
    if (oflag && oinit) {
        if ((outfile = fopen(ovalue, "w")) == NULL) {
            printf("Can't open output file (does it exist?). Exiting.\n");
            exit (1);
        }
    } else if (oinit && !oflag) {
        printf("Invalid parameter passed through -o (is it empty?). Exiting.\n");
        exit (1);
    } else {
        outfile = stdout;
    }

    FILE *infile;
    if (iflag && iinit) {
        if ((infile = fopen(ivalue, "r")) == NULL) {
            printf("Can't open input file (does it exist?). Exiting.\n");
            exit (1);
        }
    } else if (iinit && !iflag) {
        printf("Invalid parameter passed through -i (is it empty?). Exiting.\n");
        exit (1);
    } else {
        infile = stdin;
    }

    if (gen == 0 || (ginit == TRUE && gflag == FALSE)) {
            printf("Invalid parameter passed through -g (it should be an integer greater than 0). Exiting.\n");
            exit (1);
    }
    if (ginit == FALSE)  {
        gen = 5;
    }

    /* very useful for debugging argument parser */
    /*
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
    if (!iflag && !oflag) {
        putchar('\n');  /* purely for aesthetic purposes */
    }
    write_out_file(outfile, &v);

    /* print stats after final generation, if required */
    if (sflag) {
        print_statistics(&v);
    }

    /* success!~ */
    return 0;
}
