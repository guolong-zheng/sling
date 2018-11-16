#include "stdhipmem.h"



int to_remove(Node * z){
    return random();
}
// 1 if x should be removed
// 0 otherwise

Node * filter(Node * h)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * i = h;
  Node * j = NULL;
  while(i != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    if (to_remove(i)) {
      Node * inxt = i->next;
      j->next = inxt;
    } else {
      j = i;
    }
    i = i->next;
  }
  return j;
}
