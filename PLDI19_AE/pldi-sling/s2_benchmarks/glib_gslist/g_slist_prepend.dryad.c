#include "stdhipmem.h"



Node * g_slist_prepends (Node * list, int data)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * new_list = (Node *) malloc(sizeof(Node));

  new_list->key = data;
  new_list->next = list;    
  return new_list;
}

