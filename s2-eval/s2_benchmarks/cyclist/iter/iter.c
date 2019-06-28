#include "stdlib.h"
#include <assert.h>
#include <stdio.h>



struct llist *create_llist()
{
  //pre
  struct llist *l = malloc(sizeof(struct llist));
  struct node *n = malloc(sizeof(struct node));
  n->next = NULL;
  n->value = 0;
  l->first = n;
  l->last = n;
  //post
  return l;
}

struct llist * llist_add(struct llist *list, int x)
{
  //pre
  struct node *l = NULL;
  struct node *n = malloc(sizeof(struct node));
  n->next = NULL;
  n->value = 0;
  l = list->last;
  l->next = n;
  l->value = x;
  list->last = n;
  //post
  return list;
}


void llist_append(struct llist *list1, struct llist *list2)
{

  struct node *l1 = list1->last;
  struct node *f2 = list2->first;
  struct node *l2 = list2->last;
  if (f2 == l2) {
    free(l2);
    free(list2);
  } else {
    l1->next = f2->next;
    l1->value = f2->value;
    list1->last = l2;
    free(f2);
    free(list2);
  }

}

void llist_dispose(struct llist *list)
{
  //pre
  struct node *n = list->first;
  struct node *l = list->last;
  struct node *next = NULL;
  while (n != l)
  {
    //loop
    next = n->next;
    free(n);
    n = next;
  }
  free(l);
  free(list);
  //post
}

int llist_length(struct llist *list)
{

  struct node *f = list->first;
  struct node *n = f;
  struct node *l = list->last;
  struct node *next = NULL;
  int c = 0;
  while (n != l)
  {

    next = n->next;
    n = next;
    if (c == 2147483647) abort();
    c = c + 1;
  }

  return c;
}

int llist_lookup(struct llist *list, int index)
{

  struct node *f = list->first;
  struct node *l = list->last;
  struct node *n = f;
  struct node *next = NULL;
  int i = 0;
  while (i < index)
  {

    next = n->next;
    n = next;
    i = i + 1;
  }
  int value = n->value;

  return value;
}

int llist_removeFirst(struct llist *l)
{

  struct node *nf = l->first;
  struct node *nfn = nf->next;
  int nfv = nf->value;
  free(nf);
  l->first = nfn;

  return nfv;
}


struct iter *llist_create_iter(struct llist *l)
{
    //pre
    struct iter *i = 0;
    struct node *f = 0;
    i = malloc(sizeof(struct iter));
    if (i == 0) {
      abort();
    }
    f = l->first;
    i->current = f;
    //post
    return i;
}

int iter_next(struct iter *i)
{
    //pre
    struct node *c = i->current;
    int value = c->value;
    struct node *n = c->next;
    i->current = n;
    //post
    return value;
}

void iter_dispose(struct iter *i)
{
    //pre
    free(i);
    //post
}

