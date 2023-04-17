#include "stdhipmem.h"



void simpleq_init()
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * head = (Node *) malloc(sizeof(Node));
  head->next = NULL;
  head->last = head;
}

