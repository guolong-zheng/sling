#include "stdlib.h"

struct node {
  struct node* next;
  int value;
};

struct stack {
  struct node* head;
};

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
  struct node* tmp = s->head;
  int res = tmp->value;
  s->head = tmp->next;
  free(tmp);
  return res;
}

void dispose(struct stack* s)
  //@ requires stack(s, ?vs);
  //@ ensures true;
{
  struct node* n = s->head;
  while(n != NULL)
    //@ invariant lseg(n, 0, ?vs0);
    //@ decreases length(vs0);
  {
    struct node* tmp = n;
    n = n->next;
    free(tmp);
  }
  free(s);
}

/*@
lemma void lseg_add(struct node* a)
  requires lseg(a, ?b, ?vs1) &*& b != 0 &*& b->next |-> ?n &*& b->value |-> ?v &*& malloc_block_node(b) &*& lseg(n, 0, ?vs2);
  ensures lseg(a, n, append(vs1, cons(v, nil))) &*& lseg(n, 0, vs2);
{
  if(a == b) {
  } else {
    lseg_add(a->next);
  }
  open lseg(n, 0, vs2);
}
lemma void append_assoc<t>(list<t> l1, list<t> l2, list<t> l3)
  requires true;
  ensures append(l1, append(l2, l3)) == append(append(l1, l2), l3);
{
  switch(l1) {
    case nil:
    case cons(h, t):
      append_assoc(t, l2, l3);
  }
}
@*/

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

int main(int argc, char **argv)
  //@ requires true;
  //@ ensures true;
{
  int size = atoi(argv[1]);
  struct stack* s = create_stack();
	int i = 0;
  for (i = 0; i < size; i++)
	{
		push(s, i);
	}
  return 0;
}
