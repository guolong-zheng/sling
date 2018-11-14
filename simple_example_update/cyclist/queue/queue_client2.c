#include "stdlib.h"
#include "queue.h"
#include "threading.h"
#include <assert.h>

struct message {
    int id;
};

struct message *create_message(int id)
{
    //pre
    struct message *message = malloc(sizeof(struct message));
    if (message == 0) abort();
    message->id = id;
    //post
    return message;
}

struct dequeue_result {
    struct message *message;
};

void consumer(struct queue *queue)
{
    //pre
    struct dequeue_result *result = malloc(sizeof(struct dequeue_result));
    if (result == 0) abort();

    int lastId = -1;
    int maxelems = get_maxelems(queue);
    while (lastId < maxelems - 1)
    {
        bool success = queue_try_dequeue(queue, &result->message);
        if (success) {
            int id = result->message->id;
            assert(lastId < id);
            lastId = id;
            free(result->message);
        }
    }
    //post
}


void enqueue(struct queue *queue, int numelements)
{
    //pre
    int id = 0;
    while (id < numelements)
    {
        //loop
        struct message *message = create_message(id);
        queue_enqueue(queue, message);
        id++;
    }
    //post
}

int main(int argc, char **argv)
{
    int numelements = atoi(argv[1]);
    struct queue *queue = create_queue(numelements);
    int i;
    for (i=0;i<numelements;i++)
    {
        struct message *message = create_message(i);
        queue_enqueue(queue, message);
    }
    queue_dispose(queue);
}
