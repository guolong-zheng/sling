#include "stdlib.h"


struct stack* create_stack()
{
  //pre
  struct stack* s = malloc(sizeof(struct stack));
  if(s == NULL) abort();
  s->head = NULL;
  //post
  return s;
}

void push(struct stack* s, int x)
  //@ requires stack(s, ?vs);
  //@ ensures stack(s, cons(x, vs));
{
  //pre
  struct node* n = malloc(sizeof(struct node));
  if(n == NULL) abort();
  n->next = s->head;
  n->value = x;
  s->head = n;
  //post
}

int pop(struct stack* s)
  //@ requires stack(s, ?vs) &*& vs != nil;
  //@ ensures stack(s, tail(vs)) &*& result == head(vs);
{
  //pre
  struct node* tmp = s->head;
  int res = tmp->value;
  s->head = tmp->next;
  free(tmp);
  //post
  return res;
}

void dispose(struct stack* s)
  //@ requires stack(s, ?vs);
  //@ ensures true;
{
  //pre
  struct node* n = s->head;
  while(n != NULL)
    //@ invariant lseg(n, 0, ?vs0);
    //@ decreases length(vs0);
  {
    //loop
    struct node* tmp = n;
    n = n->next;
    free(tmp);
  }
  free(s);
  //post
}

int get_length(struct stack* s)
  //@ requires stack(s, ?vs);
  //@ ensures stack(s, vs) &*& result == length(vs);
{
  int r = 0;
  //@ struct node* head = s->head;
  struct node* n = s->head;
  while(n != NULL)
    //@ invariant lseg(head, n, ?vs0) &*& lseg(n, 0, ?vs1) &*& r == length(vs0) &*& vs == append(vs0, vs1);
    //@ decreases length(vs1);
  {
    r = r + 1;
    n = n->next;
    //@ lseg_add(head);
    //@ append_assoc(vs0, cons(head(vs1), nil), tail(vs1));
  }
  return r;
}
