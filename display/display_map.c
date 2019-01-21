#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "display_map.h"

int analize_state_and_display(char **matrix_b, points_state_ammo *state)
{
    char matrix[HEIGTH][WIDTH];
    for (int i = 0, k = 0;; ++i)
    {
        memcpy(matrix, matrix_b, HEIGTH * WIDTH);
        if (state->state == -1)
            return 0;
        clean_screen();

        k = roll_matrix_and_rand_stones(matrix, WIDTH / 2);
        print_matrix(matrix);
        state->points += 1;
        if (i % (HEIGTH / 4) == 0)
            state->ammo = state->ammo >= 5 ? 5 : state->ammo + 1;
        print_ammo_and_points(state->ammo, i);
        if (k != 0)
        {
            state->state = -1;
            return 0;
        }
        memcpy(matrix_b, matrix, HEIGTH * WIDTH);
        usleep(500 * 1000);
    }
    return 0;
}

void display_map_thread(char **matrix, points_state_ammo *state)
{
    state->ammo = 5;
    state->points = 0;
    state->state = 0;
    analize_state_and_display(matrix, state);
    exit(0);
}
