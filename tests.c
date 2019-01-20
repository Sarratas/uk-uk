#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>

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

int interactive_test_queue()
{
    queue my_queue = *get_queue();
    for (int i = 0, k; i < QUEUE_SIZE + 3; ++i)
    {
        scanf("%d", &k);
        enqueue(&my_queue, k % 5);
        printf("deq %d\n", dequeue(&my_queue));
    }
    return 0;
}

void *get_shared_memory(size_t size)
{
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_ANONYMOUS | MAP_SHARED;
    return mmap(NULL, size, protection, visibility, 0, 0);
}

int test_shared_memory_queue()
{
    queue *q = get_queue();
    void *queue_pointer = get_shared_memory(sizeof(*q));
    memcpy(queue_pointer, q, sizeof(*q));
    pid_t pid[2];
    pid[0] = fork();
    if (pid[0] == 0)
    {
        queue *qq = (queue *)queue_pointer;
        enqueue(qq, LEFT);
        printf("en: %d\n", LEFT);
        enqueue(qq, SHOOT);
        printf("en: %d\n", SHOOT);
        enqueue(qq, SHOOT);
        printf("en: %d\n", SHOOT);
        enqueue(qq, SHOOT);
        printf("en: %d\n", RIGHT);
        enqueue(qq, SHOOT);
        printf("en: %d\n", SHOOT);
        usleep(1000 * 1000);
        enqueue(qq, SHOOT);
        printf("en: %d\n", SHOOT);
        enqueue(qq, SHOOT);
        printf("en: %d\n", SHOOT);
        // memcpy(queue_pointer, qq, sizeof(*qq));
        // free(qq);
        exit(0);
    }
    pid[1] = fork();
    if (pid[1] == 0)
    {
        queue *qq = (queue *)queue_pointer;
        printf("de: %d\n", dequeue(qq));
        printf("de: %d\n", dequeue(qq));
        usleep(1000 * 1000);
        printf("de: %d\n", dequeue(qq));
        printf("de: %d\n", dequeue(qq));
        // memcpy(queue_pointer, qq, sizeof(*qq));
        // free(qq);
        exit(0);
    }
    waitpid(pid[0], NULL, 0);
    waitpid(pid[1], NULL, 0);
    return 0;
}

int main(int argc, char *argv[])
{
    // test_queue();
    // printf("\n");
    test_shared_memory_queue();
    // printf("\n");
    // interactive_test_queue();
    return 0;
}
