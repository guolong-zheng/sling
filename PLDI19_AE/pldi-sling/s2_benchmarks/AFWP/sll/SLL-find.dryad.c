#include "stdhipmem.h"



int has_property(Node * x){
  return random();
}
// 1 if x has desired propertiy
// 0 otherwise

Node * SLL_find(Node * h)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * i = h;
  Node * j = NULL;
  Node * t = NULL;
  while(i != NULL && t == NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    if(has_property(i)) {
      t = i;
    } else {
      i = i->next;
    }
  }
  return t;
}
