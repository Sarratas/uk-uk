#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../utils.h"
#include "moves.h"

int read_and_enqueue(queue *q_b, int *state)
{
    unsigned char tmp = 0;
    queue *q = get_queue();
    while (1)
    {
        if (*state == -1)
            return 0;

        tmp = getchar();

        switch (tmp)
        {
        case KEY_STOP:
            memcpy(q, q_b, sizeof(queue));
            enqueue(q, STOP);
            memcpy(q_b, q, sizeof(queue));
            return 0;
            break;
        case KEY_LEFT:
            memcpy(q, q_b, sizeof(queue));
            enqueue(q, LEFT);
            memcpy(q_b, q, sizeof(queue));
            break;
        case KEY_RIGHT:
            memcpy(q, q_b, sizeof(queue));
            enqueue(q, RIGHT);
            memcpy(q_b, q, sizeof(queue));
            break;
        case KEY_SPACE:
            memcpy(q, q_b, sizeof(queue));
            enqueue(q, SHOOT);
            memcpy(q_b, q, sizeof(queue));
            break;
        default:
            break;
        }
        usleep(1000);
    }
    free(q);
    return 0;
}

void controls_thread(void *queue_pointer, int *state)
{
    queue *q = (queue *)queue_pointer;
    read_and_enqueue(q, state);
#ifdef DEBUG
    printf("controls thread exit\n");
#endif
    exit(0);
}
