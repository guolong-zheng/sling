#include "header.h"
#include <stdlib.h>

Node * split(Node * x)
{
  Node * z = x;

  Node * curr = x;
  while(curr != NULL)
  {
    z = z->next;
    curr = curr->next;
    if (curr != NULL) {
      curr = curr->next;
    }
  }
  if (z != NULL) {
    Node * tmp = z;
    z = z->next;
    tmp->next = NULL;
  }

  return z;
}

Node * merge(Node * a, Node * b)
{

  Node * res = NULL;
  if (a == NULL) {
    return b;
  } else if (b == NULL) {
    return a;
  } else if (a->key <= b->key) {
    res = a;
    a = a->next;
  } else {
    res = b;
    b = b->next;
  }

  Node * last;
  last = res;

  while(a != NULL || b != NULL)
   {
    if (a == NULL || (b != NULL && a->key > b->key)) {
      last->next = b;
      last = b;
      b = b->next;
    } else {
      last->next = a;
      last = a;
      a = a->next;
    }
  }

  return res;
}

Node * merge_sort(Node * lst)
{
  //pre
  Node * lst1 = split(lst);
  Node * a = merge_sort(lst1);
  Node * b = merge_sort(lst);
  return merge(a, b);
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_list(size);
    Node * res = merge_sort(lst);
    //post
    return 0;
}
