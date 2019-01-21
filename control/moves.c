#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "moves.h"

int read_and_enqueue(queue *q_b, points_state_ammo *state)
{
    unsigned char tmp = 0;
    queue *q = q_b;
    while (1)
    {
        if (state->state == -1)
            break;
        tmp = getchar();
        if (state->state == -1)
            break;
        switch (tmp)
        {
        case KEY_STOP:
            enqueue(q, STOP);
            return 0;
            break;
        case KEY_LEFT:
            enqueue(q, LEFT);
            break;
        case KEY_RIGHT:
            enqueue(q, RIGHT);
            break;
        case KEY_SPACE:
            enqueue(q, SHOOT);
            break;
        default:
            break;
        }
    }
    return 0;
}

void controls_thread(void *queue_pointer, points_state_ammo *state)
{
    queue *q = (queue *)queue_pointer;
    read_and_enqueue(q, state);
#ifdef DEBUG
    printf("controls thread exit\n");
#endif
    exit(0);
}
