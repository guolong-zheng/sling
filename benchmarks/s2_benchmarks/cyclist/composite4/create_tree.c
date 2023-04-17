#include "stdhipmem.h"

struct node * create_node(struct node * p)
{
  //pre
  struct node *n = malloc(sizeof(struct node));
  n->left = NULL;
  n->right = NULL;
  if(p == NULL)
    n->parent = NULL;
  else
    n->parent = p;
  n->count = 1;
  //post
  return n;
}

struct node *create_tree()
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{
  //pre
  struct node *n = create_node(NULL);
  //post
  return n;
}


