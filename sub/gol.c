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
    int max_index = 0;      /* track array size (same for both arrays) */
    int width = 0;          /* store width of grid*/
    int height = 0;         /* and height of grid*/
    int c = 0;              /* store current character */
    int x = 0, y = 0;       /* track which cell we're at */
    int first_entry = TRUE; /* is this the first coord we're recording? */

    while ((c = getc(infile))!=EOF) {
        if (x == 511 && c != '\n') {  /* w.r.t. 511: we're incrementing from zero, remember~ */
            printf("Column is over 512 characters wide (incl. newline). Exiting.\n");
            exit(1);
        }
        if (c == '.') {
        } else if (c == '\n') {
            /* new row reached */
            if (x == 0) {
                printf("You have entered a blank line. Exiting.\n");
                exit(1);
            } y += 1;
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
                if (u->living_cells_x == NULL || u->living_cells_y == NULL) {
                    printf("Memory allocation failure. Exiting.\n");
                    exit(1);
                }
                u->living_cells_x[0] = x;
                u->living_cells_y[0] = y;
                first_entry = FALSE;
            } else {
                u->living_cells_x = realloc(u->living_cells_x, (1 + max_index) * sizeof(int));
                if (u->living_cells_x == NULL) {
                    printf("Memory allocation failure. Exiting.\n");
                    exit(1);
                }
                u->living_cells_x[max_index] = x;

                u->living_cells_y = realloc(u->living_cells_y, (1 + max_index) * sizeof(int));
                if (u->living_cells_y == NULL) {
                    printf("Memory allocation failure. Exiting.\n");
                    exit(1);
                }
                u->living_cells_y[max_index] = y;
            }
            max_index += 1;
        } else {
            printf("The input file contains invalid character '%c'. Exiting.\n", c);
            exit (1);
        }
        x += 1;
    }
    if (width == 0) {
        printf("Empty input. Exiting.\n");
        exit(1);
    }
    height = y++;

    /* assigning local variables to the actual struct */
    u->width = width;
    u->height = height;
    u->num_living_cells = max_index;
    u->total_cells_ever_lived = max_index;
    u->num_generations = 1;

    int i;
    for (i = 0; i < u->num_living_cells; i++) {
        //printf("%d, %d\n", u->living_cells_x[i], u->living_cells_y[i]);
    }
}

void write_out_file(FILE *outfile, struct universe *u)
{
    int x, y;
    for (y = 0; y < u->height; y++) {
        for (x = 0; x < u->width; x++) {
            if (is_alive(u, x, y)) {
                putc('*', outfile);
            } else {
                putc('.', outfile);
            }
        }
        putc('\n', outfile);
    }
}

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

int will_be_alive(struct universe *u, int column, int row)
{
    int x, y;
    int targetx, targety;       /* 8 targets to inspect for each one cell */
    int alive_neighbours = 0;   /* track no. neighbours currently alive */
    for (y = -1; y < 2; y++) {
        for (x = -1; x < 2; x++) {
            targetx = column + x;
            targety = row + y;
            
            if (x == 0 && y == 0) { /* we should not check the space we're targetting */
                continue;
            } else if (is_alive(u, targetx, targety)) {
                alive_neighbours += 1;
            }
            if (alive_neighbours > 3) {
                return 0;
            }
        }
    }
    if (is_alive(u, column, row) && (alive_neighbours == 2 || alive_neighbours == 3)) {
        return 1;
    } else if (!is_alive(u, column, row) && (alive_neighbours == 3)) {
        return 1;
    } else {
        return 0;
    }
}

int will_be_alive_torus(struct universe *u, int column, int row)
{
    int x, y;
    int targetx, targety;       /* 8 targets to inspect for each one cell */
    int alive_neighbours = 0;   /* track no. neighbours currently alive */
    for (y = -1; y < 2; y++) {
        for (x = -1; x < 2; x++) {
            targetx = column + x;
            targety = row + y;

            /* fix OOB values for x */
            while ((targetx) < 0) { /* change negative to positive */
                targetx += u->width;
            }
            if ((targetx) > (u->width - 1)) {  /* => too high, so get the x back in range of the grid */
                targetx = targetx % u->width;
            }
            /* same for y */
            while ((targety) < 0) { /* change negative to positive */
                targety += u->height;
            }
            if ((targety) > (u->height - 1)) {  /* => too high, so get the y back in range of the grid */
                targety = targety % u->height;
            }

            if (x == 0 && y == 0) { /* we should not check the space we're targetting */
                continue;
            } else if (is_alive(u, targetx, targety)) {
                alive_neighbours += 1;
            }
            if (alive_neighbours > 3) {
                return 0;
            }
        }
    }
    if (is_alive(u, column, row) && (alive_neighbours == 2 || alive_neighbours == 3)) {
        return 1;
    } else if (!is_alive(u, column, row) && (alive_neighbours == 3)) {
        return 1;
    } else {
        return 0;
    }
}

void evolve (struct universe *u, int(*rule)(struct universe *u, int column, int row))
{
    if (u->num_living_cells > 0) {
        int x, y;
        int array_length = u->width * u->height;
        int newx[array_length];
        int newy[array_length];
        int i = 0, j = 0;
        for (y = 0; y < u->height; y++) {
            for (x = 0; x < u->width; x++) {
                if (rule(u, x, y)) {
                    newx[i] = x;
                    newy[i] = y;
                    i++;
                }
            }
        }
        free(u->living_cells_x);
        free(u->living_cells_y);
        u->living_cells_x = malloc((i+1)*sizeof(int));
        u->living_cells_y = malloc((i+1)*sizeof(int));

        if (u->living_cells_x == NULL || u->living_cells_y == NULL) {
            printf("Memory allocation failure. Exiting.\n");
            exit(1);
        }
        while (j < i) {
            u->living_cells_x[j] = newx[j];
            u->living_cells_y[j] = newy[j];
            j++;
            //printf("new cell at %d, %d\n", newx[j], newy[j]);
        }
        
        /* update stats */
        u->num_living_cells = j;
        u->total_cells_ever_lived += j;
        u->num_generations += 1.0;
    }
}

void print_statistics(struct universe *u)
{
    printf("\n%3.3f%% of cells currently alive\n", 100*(u->num_living_cells/(u->width*u->height)));
    printf("%3.3f%% of cells alive on average\n", 100*(u->total_cells_ever_lived / (u->width*u->height*u->num_generations)));
}
