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
  struct node *n = malloc(sizeof(struct node));
  if (n == NULL) { abort(); }
  n->left = NULL;
  n->right = NULL;
  n->parent = p;
  n->count = 1;
  return n;
}

struct node *create_tree()
{
  struct node *n = create_node(0);
  return n;
}

int subtree_get_count(struct node *node)
{
  int result = 0;
  if (node != NULL) { result = node->count; }
  return result;
}

void fixup_ancestors(struct node * n, struct node * p, int count)
{
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
    if (2147483647 - 1 - leftCount < rightCount) {
      abort();
    }
    {
      int pcount = 1 + leftCount + rightCount;
      p->count = pcount;
      fixup_ancestors(p, grandparent, pcount);
    }
  }
}

struct node *tree_add_left(struct node *node)
{
  struct node *n = create_node(node);
  {
      struct node *nodeLeft = node->left;
      node->left = n;
      fixup_ancestors(n, node, 1);
  }
  return n;
}

struct node *tree_add_right(struct node *node)
{
    struct node *n = create_node(node);
    {
        struct node *nodeRight = node->right;
        node->right = n;
        fixup_ancestors(n, node, 1);
    }
    return n;
}

struct node *tree_get_parent(struct node *node)
{
  struct node *p = node->parent;
  return p;
}

void subtree_dispose(struct node *node)
{
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
}

void tree_dispose(struct node *node)
{
  subtree_dispose(node);
}

int main0()
{
  struct node *node = create_tree();
  node = tree_add_left(node);
  node = tree_add_right(node);
  node = tree_get_parent(node);
  node = tree_add_left(node);
  node = tree_get_parent(node);
  node = tree_get_parent(node);
  tree_dispose(node);
  return 0;
}

void main(int argc, char **argv)
{
    int numnodes = atoi(argv[1]);
    unsigned int seed  = atoi(argv[2]);
    srand(seed);
    int i = 1;
    struct node *root = create_tree();
    struct node *leftholes[numnodes];
    struct node *rightholes[numnodes];
    leftholes[0] = root;
    rightholes[0] = root;
    int numleftholes = 1;
    int numrightholes = 1;
    while (i < numnodes)
    {
        int direction = rand() % 2;
        int j;
        if (direction) {
            j = rand() % numleftholes;
            leftholes[j] = tree_add_left(leftholes[j]);
            rightholes[numrightholes++] = leftholes[j];
        } else {
            j = rand() % numrightholes;
            rightholes[j] = tree_add_right(rightholes[j]);
            leftholes[numleftholes++] = rightholes[j];
        }
        i++;
    }
    tree_dispose(root);
}

int verifast_main()
{
    struct node *root = create_tree();
    struct node *left = tree_add_left(root);
    struct node *leftRight = tree_add_right(left);
    struct node *leftRightParent = tree_get_parent(leftRight);
    //@ assert leftRightParent == left;
    struct node *leftLeft = tree_add_left(left);
    //@ change_focus(leftLeft, left(right(here)), leftRight);
    struct node *leftRightRight = tree_add_right(leftRight);
    //@ change_focus(leftRightRight, left(left(here)), leftLeft);
    //@ change_focus(leftLeft, here, root);
    tree_dispose(root);
    return 0;
}
