#include "stdhipmem.h"



Node * g_slist_insert_before(Node * slist, Node * sibling, int data)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
 
  if (slist == NULL) {
    
    slist = (Node *) malloc (sizeof (Node));

    
    slist->key = data;

    slist->next = NULL;

    return slist;
  }
  
  Node * node = NULL;
  Node * last = NULL;
  node = slist;
 
  while(node != NULL && node != sibling) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    last = node;
    node = last->next;
  }
  
  if (last == NULL) {
    node = (Node *) malloc (sizeof(Node));

    node->key = data;
    node->next = slist;
    return node;
  } else {
    node = (Node *) malloc (sizeof(Node));

    Node * tmp_last = last->next;
    node->key = data;
    node->next = tmp_last;
    last->next = node;
    return slist;
  }
}
