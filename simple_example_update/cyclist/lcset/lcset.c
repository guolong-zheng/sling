#include "stdlib.h"
#include "atomics.h"
#include "locks.h"
#include "lcset.h"
#include <limits.h>

struct node {
    void *lock;
    struct node *next;
    int value;
};

struct set {
    struct node *head;
    int maxelems;
};

struct set *create_set(int maxelems)
{
    //pre
    struct node *first = malloc(sizeof(struct node));
    if (first == 0) abort();
    struct node *last = malloc(sizeof(struct node));
    if (last == 0) abort();
    first->lock = 0;
    first->value = INT_MIN;
    first->next = last;
    last->value = INT_MAX;
    struct set *set = malloc(sizeof(struct set));
    if (set == 0) abort();
    set->head = first;
    set->maxelems = maxelems;
    //post
    return set;
}

int get_maxelems(struct set *set)
{
    return set->maxelems;
}

void dispose_set(struct set *set)
{
    //pre
    struct node *x = set->head;
    while (x->value < INT_MAX)
    {
        //loop
        struct node *y = x->next;
        free(x);
        x = y;
    }
    free(x);
    free(set);
    //post
}

struct node *locate(struct set *set, int e)
{
    //pre
    struct node *p = set->head;
    {
        lock(&p->lock);
    }
    struct node *c = p->next;
    if (c->value < e) {
        {
            lock(&c->lock);
        }
        {
            unlock(&p->lock);
        }
        p = c;
        goto loop;
    }
    //post
    return p;
}

bool contains(struct set *set, int e)
{
    //pre
    struct node *head = set->head;
    struct node *x = locate(set, e);
    struct node *z = x->next;
    bool result = z->value == e;
    {
        unlock(&x->lock);
    }
    //post
    return result;
}

bool add(struct set *set, int e)
{
    //pre
    struct node *head = set->head;
    struct node *x = locate(set, e);
    struct node *z = x->next;
    bool result = false;
    struct node *y = 0;
    if (z->value != e) {
        y = malloc(sizeof(struct node));
        if (y == 0) abort();
        y->lock = 0;
        y->value = e;
        y->next = z;
        x->next = y;
        result = true;
    }
    {
        unlock(&x->lock);
    }
    //post
    return result;
}

bool _remove(struct set *set, int e)
{
    //pre
    struct node *head = set->head;
    struct node *x = locate(set, e);
    struct node *y = x->next;
    bool result = y->value == e;
    if (result) {
        {
            lock(&y->lock);
        }
        x->next = y->next;
        free(y);
    }
    {
        unlock(&x->lock);
    }
    //post
    return result;
}
