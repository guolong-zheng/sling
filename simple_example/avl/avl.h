#ifndef AVL_H_
#define AVL_H_

typedef struct a_node {
  struct a_node * left;
  struct a_node * right;
  int key;
  int height;
} AVLNode;

AVLNode * create_avl(int size);
int get_height(AVLNode * x);
AVLNode * avl_balance(AVLNode * x);
int avl_find_smallest(AVLNode * x);
AVLNode * avl_delete(AVLNode * x, int k);
AVLNode * avl_insert(AVLNode * x, int k);

#endif
