#include "stdlib.h"
#include <assert.h>
#include <stdio.h>

struct node {
  struct node *next;
  int value;
};

struct llist {
  struct node *first;
  struct node *last;
};

struct iter {
    struct node *current;
};

struct llist *create_llist()
{
  struct llist *l = malloc(sizeof(struct llist));
  if (l == NULL) abort();
  struct node *n = malloc(sizeof(struct node));
  n->next = NULL;
  n->value = 0;
  if (n == NULL) abort();
  l->first = n;
  l->last = n;
  return l;
}

struct llist * llist_add(struct llist *list, int x)
{
  //pre
  struct node *l = NULL;
  struct node *n = malloc(sizeof(struct node));
  n->next = NULL;
  n->value = 0;
  if (n == NULL) {
    abort();
  }
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

  struct node *n = list->first;
  struct node *l = list->last;
  struct node *next = NULL;
  while (n != l)
  {

    next = n->next;
    free(n);
    n = next;
  }
  free(l);
  free(list);

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

void main0()
{
  struct llist *l = create_llist();
  llist_add(l, 10);
  llist_add(l, 20);
  llist_add(l, 30);
  llist_add(l, 40);
  int x1 = llist_removeFirst(l);
  assert(x1 == 10);
  int x2 = llist_removeFirst(l);
  assert(x2 == 20);
  llist_dispose(l);
}

struct iter *llist_create_iter(struct llist *l)
{

    struct iter *i = 0;
    struct node *f = 0;
    i = malloc(sizeof(struct iter));
    if (i == 0) {
      abort();
    }
    f = l->first;
    i->current = f;

    return i;
}

int iter_next(struct iter *i)
{

    struct node *c = i->current;
    int value = c->value;
    struct node *n = c->next;
    i->current = n;

    return value;
}

void iter_dispose(struct iter *i)
{

    free(i);

}

int main(int argc, char *argv[])
{
	int size = atoi(argv[1]);
    struct llist *l = create_llist();
	int i, j; struct iter *it;
	for (i=0;i<size;i++)
	{
		llist_add(l, i);
		it = llist_create_iter(l);
		for (j=0;j<i;j++)
		{
			iter_next(it);
		}
		iter_dispose(it);
	}
}

int main1(int argc, char * argv[])
{
  int size;
  sscanf(argv[1],"%d",&size);
  struct llist *l1 = create_llist();
  struct llist *l2 = create_llist();
  llist_add(l1, 10);
  llist_add(l1, 20);
  llist_add(l1, 30);
  llist_add(l2, 40);
  llist_add(l2, 50);
  llist_add(l2, 60);
  int x = llist_removeFirst(l2); assert(x == 40);
  llist_append(l1, l2);
  int n = llist_length(l1); assert(n == 5);
  int e0 = llist_lookup(l1, 0); assert(e0 == 10);
  int e1 = llist_lookup(l1, 1); assert(e1 == 20);
  int e2 = llist_lookup(l1, 2); assert(e2 == 30);
  int e3 = llist_lookup(l1, 3); assert(e3 == 50);
  int e4 = llist_lookup(l1, 4); assert(e4 == 60);
  struct iter *i1 = llist_create_iter(l1);
  struct iter *i2 = llist_create_iter(l1);
  int i1e1 = iter_next(i1); assert(i1e1 == 10);
  int i2e1 = iter_next(i2); assert(i2e1 == 10);
  int i1e2 = iter_next(i1); assert(i1e2 == 20);
  int i2e2 = iter_next(i2); assert(i2e2 == 20);
  int i1e3 = iter_next(i1); assert(i1e3 == 30);
  int i2e3 = iter_next(i2); assert(i2e3 == 30);
  int i1e4 = iter_next(i1); assert(i1e4 == 50);
  int i2e4 = iter_next(i2); assert(i2e4 == 50);
  int i1e5 = iter_next(i1); assert(i1e5 == 60);
  int i2e5 = iter_next(i2); assert(i2e5 == 60);
  iter_dispose(i1);
  iter_dispose(i2);
  llist_dispose(l1);
  return 0;
}


int main2()
{
    struct llist *l = create_llist();
    llist_add(l, 5);
    llist_add(l, 10);
    llist_add(l, 15);
    struct iter *i1 = llist_create_iter(l);
    struct iter *i2 = llist_create_iter(l);
    int i1e1 = iter_next(i1); assert(i1e1 == 5);
    int i2e1 = iter_next(i2); assert(i2e1 == 5);
    int i1e2 = iter_next(i1); assert(i1e2 == 10);
    int i2e2 = iter_next(i2); assert(i2e2 == 10);
    iter_dispose(i1);
    iter_dispose(i2);
    llist_dispose(l);
    return 0;
}
