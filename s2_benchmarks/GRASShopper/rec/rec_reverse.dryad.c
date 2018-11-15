
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
} Node;

Node * rec_reverse_acc(Node * curr, Node * rev)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (curr == NULL) {
    return rev;
  } else {
    Node * tmp = curr->next;
    curr->next = rev;
    Node * ret = rec_reverse_acc(curr, tmp);
    return ret;
  }
}

Node * rec_reverse(Node * lst) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  return rec_reverse_acc(lst, NULL);
}
