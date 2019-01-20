#include <stdlib.h>
#include <sys/mman.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#include "utils.h"

int init_queue(queue *object)
{
    object->first = 0;
    object->last = 0;
    for (int i = 0; i < QUEUE_SIZE; ++i)
    {
        object->elements[i].next = (i + 1) % QUEUE_SIZE;
        object->elements[i].prev = i - 1 < 0 ? QUEUE_SIZE - 1 : i - 1;
        object->elements[i].move = 0;
    }
    return 0;
}

queue *get_queue()
{
    queue *my_queue = malloc(sizeof(queue));
    init_queue(my_queue);
    return my_queue;
}

int enqueue(queue *q, int move)
{
    q->elements[q->last].move = move;
    q->last = q->elements[q->last].next;
    return 0;
}

int dequeue(queue *q)
{
    if (q->first == q->last)
        return -1;
    enum moves current = q->elements[q->first].move;
    q->first = q->elements[q->first].next;
    return current;
}

void *get_shared_memory(size_t size)
{
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_ANONYMOUS | MAP_SHARED;
    return mmap(NULL, size, protection, visibility, 0, 0);
}
