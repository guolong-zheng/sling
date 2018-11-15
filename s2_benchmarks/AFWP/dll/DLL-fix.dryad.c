#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
  struct node * prev;
} DLNode;

DLNode * polarize(DLNode * h) 
/*@
   infer[@shape]
   requires true
   ensures true;
 */
{
  Node * i = h;
  DLNode * j = NULL;
  while(i != NULL) 
  { 
    DLNode * k = j;
    j = (DLNode *) malloc(sizeof(DLNode));
    _(assume j != NULL)
    j->next = k;
    k->prev = j;
    i = i->next;
  }
  return j;
}
