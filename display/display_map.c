#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "display_map.h"

int analize_state_and_display(char **matrix_b, int *state)
{
    char matrix[HEIGTH][WIDTH];
    for (int i = 0, k = 0;; ++i)
    {
        memcpy(matrix, matrix_b, HEIGTH * WIDTH);
        if (*state == -1)
            return 0;
        clean_screen();

        k = roll_matrix_and_rand_stones(matrix, 3);
        print_matrix(matrix);
        print_ammo_and_points(0, i);
        if (k != 0)
        {
            *state = -1;
            return 0;
        }
        memcpy(matrix_b, matrix, HEIGTH * WIDTH);
        usleep(500 * 1000);
    }
    return 0;
}

void display_map_thread(char **matrix, int *state)
{
    analize_state_and_display(matrix, state);
    exit(0);
}
