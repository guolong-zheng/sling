#include "header.h"
#include <stdio.h>
#include <stdlib.h>

BNode * bst_find_iter(BNode * x, int k)
{
    //pre
  BNode * curr = x;
  while(curr != NULL)
  {
     //loop
    if (curr->key == k) {
        //post
      return curr;
    } else if (k < curr->key) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  //post
  return curr;
}

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    BNode * root = create_tree(size);

    BNode * res = bst_find_iter(root, rand_num());
    return 0;
}
