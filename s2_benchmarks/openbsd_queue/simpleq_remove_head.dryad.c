
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
  struct node * last;
} Node;

void simpleq_remove_head(Node * head) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * fst = head->next;
  Node * fstn = fst->next;
  head->next =fstn;
  if (fstn == NULL) {
    head->last = head;
  }
  free(fst);
}
