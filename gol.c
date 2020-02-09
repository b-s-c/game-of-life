#include <stdlib.h>
#include "gol.h"

#define TRUE    1
#define FALSE   0

/* gol.c: the definitions of the functions declared in gol.h
 ************************************************************
 * void read_in_file(FILE *infile, struct universe *u);
 * void write_out_file(FILE *outfile, struct universe *u);
 * int is_alive(struct universe *u, int column, int row);
 * int will_be_alive(struct universe *u, int column, int row);
 * int will_be_alive_torus(struct universe *u,  int column, int row);
 * void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row));
 * void print_statistics(struct universe *u);
*/

void read_in_file(FILE *infile, struct universe *u)
{
    /*if ((infile = fopen("glider.txt", "r")) == NULL) {
        printf("Can't open file\n");
        exit (1);
    }*/

    int max_index = 0;      /* track array size (same for both arrays) */
    int width = 0;          /* store width of grid*/
    int height = 0;         /* and height of grid*/
    int c = 0;              /* store current character */
    int x = 0, y = 0;       /* track which cell we're at */
    int first_entry = TRUE; /* is this the first coord we're recording? */
    //int *newp;              /* new pointer for when we need to extend the array */

    /* if file supplied~ */
    while ((c = getc(infile))!=EOF) {
        if (x == 511 && c != '\n') {  /* w.r.t. 511: we're incrementing from zero, remember~ */
            printf("Column is over 512 characters wide (incl. newline). Exiting.\n");
            exit(1);
        }
        if (c == '.') {
        } else if (c == '\n') {
            /* new row reached */
            y += 1;
            if (width == 0) {
                width = x++;
            } else if (x++ != width) {
                printf("Inconsistent line widths. Exiting.\n");
                exit(1);
            }
            x = 0;
            continue;
        } else if (c == '*') {
            /* record x and y values to arrays in struct */
            if (first_entry == TRUE) {
                u->living_cells_x = malloc(1 * sizeof(int));
                u->living_cells_y = malloc(1 * sizeof(int));
                u->living_cells_x[0] = x;
                u->living_cells_y[0] = y;
                first_entry = FALSE;
            } else {
                u->living_cells_x = realloc(u->living_cells_x, (1 + max_index) * sizeof(int));
                if (u->living_cells_x == NULL) {
                    printf("Out of memory\n");
                    exit(1);
                }
                u->living_cells_x[max_index] = x;

                u->living_cells_y = realloc(u->living_cells_y, (1 + max_index) * sizeof(int));
                if (u->living_cells_y == NULL) {
                    printf("Out of memory\n");
                    exit(1);
                }
                u->living_cells_y[max_index] = y;
            }
            max_index += 1;
        } else {
            printf("The input file contains invalid character '%c'.\n", c);
            exit (1);
        }
        x += 1;
    }
    height = y++;

    /* assigning local variables to the actual struct */
    u->width = width;
    u->height = height;
    u->num_living_cells = max_index;

    /*int i;
    for (i = 0; i < u->num_living_cells; i++) {
        printf("%d, %d\n", u->living_cells_x[i], u->living_cells_y[i]);
    }
    printf("num living cells: %d\n", u->num_living_cells);
    printf("w: %d, h: %d\n", u->width, u->height);*/
}

/* void write_out_file(FILE *outfile, struct universe *u)
{
    
} */

int is_alive(struct universe *u, int column, int row)
{
    int i;
    for (i = 0; i < u->num_living_cells; i++) {
        if (column == u->living_cells_x[i]) {
            if (row == u->living_cells_y[i]) {
                /*printf("found you\n");*/
                return 1;
            }
        }
    }
    /*printf("where are you :(\n");*/
    return 0;
}
