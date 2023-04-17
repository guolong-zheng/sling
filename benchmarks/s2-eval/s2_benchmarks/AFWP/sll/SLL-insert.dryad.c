#include "stdhipmem.h"



Node * SLL_insert(Node * h, int v) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * i = h;
  Node * j = NULL;
  while(i != NULL && i->key <= v) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    j = i;
    i = i->next;
  }
  if (i == h) {
    Node * hd = (Node *)malloc(sizeof(Node));

    hd->key = v;
    hd->next = i;
    return hd;
  } 
  else {
    Node * e = (Node *)malloc(sizeof(Node));

    
    e->key = v;
    j->next = e;
    e->next = i;
    return h;
  } 
}
