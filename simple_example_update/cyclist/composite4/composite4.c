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

int main(int argc, char **argv)
{
    int numnodes = atoi(argv[1]);
    unsigned int seed  = 10;
    srand(seed);
    int i = 1;
    struct node *root = create_tree();
    struct node *leftholes[numnodes];
    struct node *rightholes[numnodes];
    leftholes[0] = root;
    rightholes[0] = root;
    int numleftholes = 1;
    int numrightholes = 1;
    int direction = 0;
    int j = 0;
    while (i < numnodes)
    {
        direction = rand() % 2;
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

    return 0;
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
