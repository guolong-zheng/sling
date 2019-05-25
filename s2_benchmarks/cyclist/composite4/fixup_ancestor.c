#include "stdhipmem.h"

int subtree_get_count(struct node *node)
{
  //pre
  int result = 0;
  if (node != NULL) { result = node->count; }
  //post
  return result;
}

void fixup_ancestors(struct node * n, struct node * p, int count)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{
  //pre
  if (p == NULL) {
  } else {
    struct node *left = p->left;
    struct node *right = p->right;
    struct node *grandparent = p->parent;
    int leftCount = 0;
    int rightCount = 0;
    if (n == left) {
      leftCount = count;
      rightCount = subtree_get_count(right);
    } else {
      leftCount = subtree_get_count(left);
      rightCount = count;
    }
    int pcount = 1 + leftCount + rightCount;
    p->count = pcount;
    fixup_ancestors(p, grandparent, pcount);
  }
  //post
  return;
}


