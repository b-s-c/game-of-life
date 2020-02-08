#include <stdio.h>
struct universe
{
    /* a grid of max width 512, max height infinity */
    int *living_cells_x;
    int *living_cells_y;
    /* e.g. if (5, 4) was a living cell, then for some integer 'a' living_cells_x[a] would store 5 and living_cells_y[a] would store 4 */

    /* statistics */
    double percent_currently_alive;
    double percent_alive_on_average;
    int num_generations;
};
    /*living_cells_x = malloc(sizeof(int));*/

/*Do not modify the next seven lines*/
void read_in_file(FILE *infile, struct universe *u);
void write_out_file(FILE *outfile, struct universe *u);
int is_alive(struct universe *u, int column, int row);
int will_be_alive(struct universe *u, int column, int row);
int will_be_alive_torus(struct universe *u,  int column, int row);
void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row));
void print_statistics(struct universe *u);
/*You can modify after this line again*/

