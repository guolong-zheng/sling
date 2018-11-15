
#include <stdlib.h>

typedef
struct node {
  struct node * next;
} Node;


Node * create(unsigned sz)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * h = NULL;
  while(sz > 0) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    sz --;
    Node * e = (Node *)malloc(sizeof(Node));
    _(assume e != NULL)

    e->next = h;
    h = e;
  }
  return h;
}
