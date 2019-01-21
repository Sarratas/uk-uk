#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "display_player.h"
#include "display_utils.h"

int get_player_position(char matrix[HEIGTH][WIDTH])
{
    int index = 0;
    for (; index < WIDTH && matrix[HEIGTH - 1][index] != 'X'; ++index)
        ;
    return index;
}

int dequeue_and_display(queue *q_b, char **matrix_b, points_state_ammo *state)
{
    char matrix[HEIGTH][WIDTH];
    queue *q = q_b;
    int tmp = 0;
    while (1)
    {
        if (state->state == -1)
        {
            return 0;
        }
        tmp = dequeue(q);

        if (tmp == -1)
            continue;
        if (tmp == STOP)
        {
            state->state = -1;
            return 0;
        }
        if (tmp == RIGHT || tmp == LEFT)
        {
            memcpy(matrix, matrix_b, HEIGTH * WIDTH);

            int index = get_player_position(matrix);
            int new_index = tmp == RIGHT ? (index + 1) % WIDTH : index - 1 < 0 ? WIDTH - 1 : index - 1;
            if (matrix[HEIGTH - 1][new_index] != 'X' && matrix[HEIGTH - 1][new_index] != 'i' && matrix[HEIGTH - 1][new_index] != 0)
            {
                matrix[HEIGTH - 1][index] = 0;
                matrix[HEIGTH - 1][new_index] = 'X';
                state->state = -1;
                return 0;
            }
            matrix[HEIGTH - 1][index] = 0;
            matrix[HEIGTH - 1][new_index] = 'X';
            clean_screen();
            print_matrix(matrix);
            print_ammo_and_points(state->ammo, state->points);
            memcpy(matrix_b, matrix, HEIGTH * WIDTH);
        }
        if (tmp == SHOOT)
        {
            if(state->ammo == 0)
                continue;
            memcpy(matrix, matrix_b, HEIGTH * WIDTH);
            state->ammo = state->ammo > 0 ? state->ammo - 1 : 0;
            int index = get_player_position(matrix);
            for (int i = HEIGTH - 2; i >= 0; --i)
            {
                if (matrix[i][index] == 'W')
                {
                    matrix[i][index] = 'M';
                    break;
                }
                else if (matrix[i][index] == 'M')
                {
                    matrix[i][index] = 0;
                    break;
                }
                else
                {
                    matrix[i][index] = 'i';
                }
            }
            memcpy(matrix_b, matrix, HEIGTH * WIDTH);
            clean_screen();
            print_matrix(matrix);
            print_ammo_and_points(state->ammo, state->points);
        }
    }
    return 0;
}

void display_player_thread(void *queue_pointer, char **matrix, points_state_ammo *state)
{
    dequeue_and_display((queue *)queue_pointer, matrix, state);
    exit(0);
}
