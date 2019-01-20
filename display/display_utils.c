#include <stdio.h>

#include "display_utils.h"

void clean_screen()
{
    printf("\033c");
}

void printf_colour(char *colour, char character)
{
    printf("%s%c", colour, character);
}