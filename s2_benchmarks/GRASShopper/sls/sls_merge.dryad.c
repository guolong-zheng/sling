
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
   int key;
   struct node * next;
} Node;

Node * merge(Node * a, Node * b) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
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
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
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

