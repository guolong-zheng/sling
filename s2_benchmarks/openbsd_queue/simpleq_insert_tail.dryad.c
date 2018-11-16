#include "stdhipmem.h"



void simpleq_insert_tail(Node * head, Node * listelm)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * elm = (Node *) malloc(sizeof(Node));
  elm->next = NULL;
  Node * lst = head->last;
  lst->next = elm;
  head->last = elm;
}
