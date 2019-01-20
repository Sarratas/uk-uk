#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "display_utils.h"

void clean_screen()
{
    printf("\033c");
}

void printf_colour(char *colour, char character)
{
    printf("%s%c", colour, character);
}

void print_matrix(char matrix[HEIGTH][WIDTH])
{
    for (int i = 0; i < HEIGTH; ++i)
    {
        for (int k = 0; k < WIDTH; ++k)
        {
            switch (matrix[i][k])
            {
            case 'W':
                printf_colour(GREEN, 'W');
                break;
            case 'M':
                printf_colour(YELLLOW, 'W');
                break;
            case 'X':
                printf_colour(RED, 'X');
                break;
            default:
                printf(" ");
            }
        }
        printf("\n");
    }
}

int roll_matrix_and_rand_stones(char matrix[HEIGTH][WIDTH], int number)
{
    int result = 0;
    for (int i = HEIGTH - 1; i > 0; --i)
    {
        for (int k = 0; k < WIDTH; ++k)
        {
            if (matrix[i][k] == 'X')
            {
                if (matrix[i - 1][k] != 0)
                    result = 1;
                continue;
            }
            matrix[i][k] = matrix[i - 1][k];
        }
    }
    for (int i = 0; i < WIDTH; ++i)
        matrix[0][i] = 0;
    for (int i = 0; i < number; ++i)
        matrix[0][rand() % WIDTH] = 'W';
    return result;
}

void print_ammo_and_points(int ammo, int points)
{
    printf("%s", CYNAN);
    for (int i = 0; i < WIDTH; ++i)
        printf("O");
    printf("\n");
    printf("%sAmmo: %5d  Score %5d\n", YELLLOW, ammo, points);
}
