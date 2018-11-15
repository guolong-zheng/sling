
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
} Node;

void rec_traverse(Node * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (lst != NULL) {
    Node * n = lst->next;
    rec_traverse(n);
  }
}
