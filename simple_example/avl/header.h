#ifndef HEADER_H_
#define HEADER_H_

#define MAX_RAND 2000

typedef struct a_node {
  struct a_node * left;
  struct a_node * right;
  int key;
  int height;
} AVLNode;

int rand_num();
AVLNode * create_avl(int size);
int get_height(AVLNode * x);
AVLNode * avl_balance(AVLNode * x);
int avl_find_smallest(AVLNode * x);
AVLNode * avl_delete(AVLNode * x, int k);
AVLNode * avl_insert(AVLNode * x, int k);

#endif
