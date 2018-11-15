
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
} Node;

Node * rec_copy_loop(Node * curr, Node * cp)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  if (curr == NULL) {
    return cp;
  } else {
    Node * old_cp = cp;
    cp = (Node *) malloc(sizeof(Node));
    _(assume cp != NULL)
    cp->next = old_cp;
    Node * curr_next = curr->next;
    Node * res = rec_copy_loop(curr_next, cp);
    return res;
  }
}


Node * rec_copy(Node * lst) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  return rec_copy_loop(lst, NULL);
}
