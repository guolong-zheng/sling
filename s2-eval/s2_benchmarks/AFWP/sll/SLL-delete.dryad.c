#include "stdhipmem.h"



Node * delete(Node * h, int k) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * i = h;
  Node * j = NULL;
  Node * t = NULL;
  if (i == NULL) {
    return h;
  }
 // while(i != NULL && t == NULL) 
  
  while(i != NULL && t == NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    if (i->key == k) {
      t = i;
    } else {
      j = i;
      i = i->next;
    }
  }
  
  if (i != NULL) {
    if (j == NULL){
      h = i->next;
      free(i);
    } else {
      t = i->next;
      free(i);
      j->next = t;
    }
  }
  return h;
}
