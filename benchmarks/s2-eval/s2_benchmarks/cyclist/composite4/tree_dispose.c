#include "stdhipmem.h"

void subtree_dispose(struct node *node)
/*
  infer[@shape]
  requires true
  ensures true;
*/
{
  //pre
  if (node != NULL) {
    {
      struct node *left = node->left;
      subtree_dispose(left);
    }
    {
      struct node *right = node->right;
      subtree_dispose(right);
    }
    free(node);
  }
  //post
}


