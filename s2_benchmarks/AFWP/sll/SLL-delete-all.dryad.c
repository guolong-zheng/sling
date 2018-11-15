
#include <stdlib.h>

typedef
struct node {
   int key;
   struct node * next;
} Node;

void delete_all(Node * h, int k) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{  
  Node * i = h;
  while(i != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    Node * j = i;
    i = i->next;
    j->next = NULL;
    free(j);
  }
}
  
