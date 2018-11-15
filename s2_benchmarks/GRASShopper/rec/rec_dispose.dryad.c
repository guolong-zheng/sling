
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
} Node;

void rec_dispose(Node * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (lst != NULL) {
    Node * n = lst->next;
    free(lst);
    rec_dispose(n);
  }
}
