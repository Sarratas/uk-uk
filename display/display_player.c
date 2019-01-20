#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "display_player.h"
#include "display_utils.h"
#include "../utils.h"

int get_player_position(char matrix[HEIGTH][WIDTH])
{
    int index = 0;
    for (; index < WIDTH && matrix[HEIGTH - 1][index] != 'X'; ++index)
        ;
    return index;
}

int dequeue_and_display(queue *q_b, char **matrix_b, int *state)
{
    char matrix[HEIGTH][WIDTH];
    queue *q = q_b;
    int tmp = 0;
    while (1)
    {
        if (*state == -1)
        {
            return 0;
        }
        tmp = dequeue(q);

        if (tmp == -1)
            continue;
        if (tmp == STOP)
        {
            *state = -1;
            return 0;
        }
        if (tmp == RIGHT || tmp == LEFT)
        {
            memcpy(matrix, matrix_b, HEIGTH * WIDTH);

            int index = get_player_position(matrix);
            int new_index = tmp == RIGHT ? (index + 1) % WIDTH : index - 1 < 0 ? WIDTH - 1 : index - 1;
            if (matrix[HEIGTH - 1][new_index] != 'X' && matrix[HEIGTH - 1][new_index] != 0)
            {
                matrix[HEIGTH - 1][index] = 0;
                matrix[HEIGTH - 1][new_index] = 'X';
                *state = -1;
                return 0;
            }
            matrix[HEIGTH - 1][index] = 0;
            matrix[HEIGTH - 1][new_index] = 'X';
            clean_screen();
            print_matrix(matrix);
            memcpy(matrix_b, matrix, HEIGTH * WIDTH);
        }
    }
    return 0;
}

void display_player_thread(void *queue_pointer, char **matrix, int *state)
{
    dequeue_and_display((queue *)queue_pointer, matrix, state);
    exit(0);
}
