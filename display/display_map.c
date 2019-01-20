#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "display_map.h"

int analize_state_and_display(char **matrix_b, int *state)
{
    char matrix[HEIGTH][WIDTH];
    while (1)
    {
        memcpy(matrix, matrix_b, HEIGTH * WIDTH);
        if (*state == -1)
            return 0;
        clean_screen();

#ifdef DEBUG
        printf("analize state and display %d\n", *state);
#endif
        for (int i = 0; i < HEIGTH; ++i)
        {
            for (int k = 0; k < WIDTH; ++k)
            {
                switch (matrix[i][k])
                {
                case 'W':
                    // printf_colour(GREEN, 'W');
                    printf("W");
                    break;
                case 'M':
                    // printf_colour(YELLLOW, 'W');
                    printf("W");
                    break;
                case 'X':
                    // printf_colour(BLUE, 'X');
                    printf("X");
                    break;
                default:
                    printf(" ");
                }
            }
            if (i < HEIGTH - 1)
                printf("\n");
        }
        memcpy(matrix_b, matrix, HEIGTH * WIDTH);
        usleep(500 * 1000);
    }
    return 0;
}

void display_map_thread(char **matrix, int *state)
{
    analize_state_and_display(matrix, state);
#ifdef DEBUG
    printf("exit display map thread\n");
#endif
    exit(0);
}
