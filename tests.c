#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int test_queue()
{
    queue my_queue = *get_queue();
    enqueue(&my_queue, RIGHT);
    // enqueue(&my_queue, LEFT);
    // enqueue(&my_queue, SHOOT);
    // enqueue(&my_queue, RIGHT);
    // enqueue(&my_queue, SHOOT);
    // enqueue(&my_queue, SHOOT);
    // enqueue(&my_queue, LEFT);
    // enqueue(&my_queue, SHOOT);
    // enqueue(&my_queue, LEFT);
    // enqueue(&my_queue, LEFT);
    for (int i = 0;; ++i)
    {
        enum moves move = dequeue(&my_queue);
        printf("de: %d\n", move);

        if (move == FAIL)
            break;
        if (i < 10)
        {
            int k = rand() % 3 + 1;
            enqueue(&my_queue, k);
            printf("en: %d\n", k);
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    test_queue();
    return 0;
}
