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
    queue *q = get_queue();
    int tmp = 0;
    while (1)
    {
        memcpy(q, q_b, sizeof(queue));
        tmp = dequeue(q);
        memcpy(q_b, q, sizeof(queue));

        if (tmp == -1)
            continue;
        if (tmp == STOP)
        {
#ifdef DEBUG
            printf("tmp stop: %d ", tmp);
#endif
            // *state = -1;
            return 0;
        }
        if (tmp == RIGHT || tmp == LEFT)
        {
#ifdef DEBUG
            printf("tmp move: %d ", tmp);
#endif
            memcpy(matrix, matrix_b, HEIGTH * WIDTH);

            int index = get_player_position(matrix);
            int new_index = tmp == RIGHT ? (index + 1) % WIDTH : index - 1 < 0 ? WIDTH - 1 : index - 1;
            if (matrix[HEIGTH - 1][index] != 'X' && matrix[HEIGTH - 1][index] != 0)
            {
                matrix[HEIGTH - 1][index] = 0;
                matrix[HEIGTH - 1][new_index] = 'X';
                *state = -1;
                return 0;
            }
            matrix[HEIGTH - 1][index] = 0;
            matrix[HEIGTH - 1][new_index] = 'X';
            memcpy(matrix_b, matrix, HEIGTH * WIDTH);
        }
    }
    free(q);
    return 0;
}

void display_player_thread(void *queue_pointer, char **matrix, int *state)
{
    dequeue_and_display((queue *)queue_pointer, matrix, state);
#ifdef DEBUG
    printf("exit display player thread\n");
#endif
    exit(0);
}
