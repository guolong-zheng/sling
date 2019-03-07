#include "stdhipmem.h"



Node * g_slist_append_t(Node * list, int data)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  Node * new_list = (Node *) malloc(sizeof(Node));

  new_list->key = data;
  new_list->next = NULL;
  if (list != NULL) {
    Node * last = g_slist_last(list);
    last->next = new_list;
    return list;
  } else {
    return new_list;
  }

}
