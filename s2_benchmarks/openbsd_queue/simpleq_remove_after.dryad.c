#include "stdhipmem.h"



void simpleq_remove_after(Node * head, Node * elm)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * elmn = elm->next;
  Node * elmnn = elmn->next;
  elm->next =elmnn;
  if (elmnn == NULL) {
    head->last = elm;
  }
  free(elmn);
}
