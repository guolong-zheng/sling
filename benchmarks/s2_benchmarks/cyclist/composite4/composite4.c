#include "stdlib.h"
#include <stdbool.h>

struct node {
  struct node *left;
  struct node *right;
  struct node *parent;
  int count;
};

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
{
  //pre
  struct node *n = create_node(NULL);
  //post
  return n;
}

int subtree_get_count(struct node *node)
{
  //pre
  int result = 0;
  if (node != NULL) { result = node->count; }
  //post
  return result;
}

void fixup_ancestors(struct node * n, struct node * p, int count)
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

struct node *tree_add_left(struct node *node)
{
  //pre
  struct node *n = (struct node *)malloc(sizeof(struct node));
  n->left = NULL;
  n->right = NULL;
  n->parent = node;
  n->count = 1;

  struct node *nodeLeft = node->left;
  node->left = n;
  fixup_ancestors(n, node, 1);
  //post
  return n;

}

struct node *tree_add_right(struct node *node)
{
    //pre
    struct node *n = (struct node *)malloc(sizeof(struct node));
    n->left = NULL;
    n->right = NULL;
    n->parent = node;
    struct node *nodeRight = node->right;
    node->right = n;
    fixup_ancestors(n, node, 1);
    //post
    return n;
}

struct node *tree_get_parent(struct node *node)
{
  //pre
  struct node *p = node->parent;
  //post
  return p;
}

void subtree_dispose(struct node *node)
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

void tree_dispose(struct node *node)
{
  //pre
  subtree_dispose(node);
  //post
}


