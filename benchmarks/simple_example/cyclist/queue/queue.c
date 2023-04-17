#include "stdlib.h"
#include "atomics.h"
#include "queue.h"

struct node {
    struct node *next;
    void *value;
};

struct queue {
    int maxelems;
    struct node *first;
    struct node *middle;
    struct node *last;
};


struct queue *create_queue(int numelements)
{
    //pre
    struct node *middle = malloc(sizeof(struct node));
    if (middle == 0) { abort(); }
    struct queue *queue = malloc(sizeof(struct queue));
    if (queue == 0) { abort(); }
    queue->maxelems = numelements;
    queue->first = middle;
    queue->middle = middle;
    queue->last = middle;
    //post
    return queue;
}

int get_maxelems(struct queue *queue)
{
    return queue->maxelems;
}

void queue_enqueue(struct queue *queue, void *value)
{
    //pre
    struct node *n = malloc(sizeof(struct node));
    if (n == 0) { abort(); }
    n->value = value;
    bool done = false;
    while (!done)
    {
        //loop
        struct node *last = 0;
        {
            last = atomic_load_pointer(&queue->last);
        }

        n->next = last;

        done = atomic_compare_and_store_pointer(&queue->last, last, n);
    }
    //post
}

bool queue_try_dequeue(struct queue *queue, void **pvalue)
{
    //pre
    struct node *first = queue->first;
    struct node *middle = queue->middle;
    if (first == middle) {
        struct node *last = atomic_load_pointer(&queue->last);

        if (last == middle) {
            return false;
        }
        struct node *node = last;
        struct node *prev = last->next;
        while (prev != middle)
        {
            //loop
            struct node *prevPrev = prev->next;
            prev->next = node;
            node = prev;
            prev = prevPrev;
        }
        first->next = node;
        middle = last;
        queue->middle = middle;
    } else {
        atomic_noop();
    }
    struct node *firstNext = first->next;
    *pvalue = firstNext->value;
    queue->first = firstNext;
    free(first);
    //post
    return true;
}

void queue_dispose(struct queue *queue)
{
    //pre
    struct node *first = queue->first;
    struct node *middle = queue->middle;
    struct node *last = queue->last;
    while (first != middle)
    {
        //loop
        struct node *next = first->next;
        free(first);
        first = next;
    }
    while (last != middle)
    {
        //loop
        struct node *next = last->next;
        free(last);
        last = next;
    }
    free(middle);
    free(queue);
    //post
}
