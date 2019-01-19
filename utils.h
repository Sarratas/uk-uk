#define QUEUE_SIZE 1024

enum moves
{
    NONE,
    RIGHT,
    LEFT,
    SHOOT,
    FAIL
};

typedef struct elem elem;

struct elem
{
    enum moves move;
    int next,
        prev;
};

typedef struct queue
{
    int last,
        first;
    elem elements[QUEUE_SIZE];
} queue;

int init_queue(queue *);

queue *get_queue();

int enqueue(queue *, int);

int dequeue(queue *);
