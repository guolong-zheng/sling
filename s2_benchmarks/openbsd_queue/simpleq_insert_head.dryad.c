#include "stdhipmem.h"



void simpleq_insert_head(Node * head, Node * listelm)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * elm = (Node *) malloc(sizeof(Node));
  elm->next = NULL;
  if (head->next == NULL) {
    head->last = elm;
  }
  head->next = elm;
}
