#include "prio_tree.h"

int treap_find_rec(BNode * x, int k)
{
   //pre
  if (x == NULL) {
    //post
    return 0;
  } else {
      if (k == x->key) {
        //post
        return 1;
      } else if (k < x->key) {
        int r = treap_find_rec(x->left, k);
        //post
        return r;
      } else {
        int r = treap_find_rec(x->right, k);
        //post
        return r;
    }
  }
}

int main( int argc, char * argv[]){
    int size;
    sscanf(argv[1], "%d", &size);
    BNode * root = create_tree(size);

    int res = treap_find_rec(root, rand_num());

    return 0;
}
