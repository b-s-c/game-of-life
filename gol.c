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

/* must:
 * - keep count of number of cells
 * - work out percentage alive once finished
 * - keep count of no. generations
*/
void read_in_file(FILE *infile, struct universe *u)
{
    if ((infile = fopen("glider.txt", "r")) == NULL) {
        printf("Can't open file\n");
        exit (1);
    }

    int max_index = 1;      /* track array size (same for both arrays) */
    int width = 0;          /* store width of grid*/
    int height = 0;         /* and height of grid*/
    int c = 0;              /* store current character */
    int x = 0, y = 0;       /* track which cell we're at */
    int first_entry = TRUE; /* is this the first coord we're recording? */

    /* if file supplied~ */
    while ((c=getc(infile))!=EOF) {
        if (x == 511 && c != '\n') {  /* we're incrementing from zero, remember~ */
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
                int *newp;
                newp = realloc(u->living_cells_x, max_index * sizeof(int));
                if (newp == NULL) {
                    printf("Out of memory\n");
                    exit(1);
                }
                u->living_cells_x = newp;
                u->living_cells_x[max_index] = x;

                newp = realloc(u->living_cells_y, max_index * sizeof(int));
                if (newp == NULL) {
                    printf("Out of memory\n");
                    exit(1);
                }
                u->living_cells_y = newp;
                u->living_cells_y[max_index] = y;

                max_index += 1;
            }
        } else {
            printf("The input file contains invalid character '%c'.\n", c);
            exit (1);
        }
        x += 1;
    }
    height = y++;
    int i;
    for (i = 0; i < max_index; i++) {
        printf("%d, %d\n", u->living_cells_x[i], u->living_cells_y[i]);
    }
    printf("w: %d, h: %d\n", width, height);
}
