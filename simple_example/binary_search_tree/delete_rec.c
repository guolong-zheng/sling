#include "header.h"

BNode * bst_delete_rec(BNode * x, int k)
{
    //pre
  if(x->key == k) {
    BNode * r = bst_remove_root(x);
    //post
    return r;
  } else if (k < x->key) {
    BNode * xl = x->left;
    BNode * xr = x->right;
    BNode * l = bst_delete_rec(xl, k);
    x->left = l;
    //post
    return x;
  } else {
    BNode * xl = x->left;
    BNode * xr = x->right;
    BNode * r = bst_delete_rec(xr, k);
    x->right = r;
    //post
    return x;
  }
}

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    BNode * root = create_tree(size);

    BNode * res = bst_delete_rec(root, rand_num());

    return 0;
}

BNode * bst_remove_root(BNode * x)
{
    if(x->left== NULL && x->right == NULL){
        free(x);
        return NULL;
    }else if(x->left == NULL){
        BNnode * res = x->right;
        free(x);
        return res;
    }else if(x->right == NULL){
        BNnode * res = x->left;
        free(x);
        return res;
    }else{
        BNode * tmp = find_smallest(x->right);
        x->key = tmp->key;
        bst_remove_root(tmp);
    }
}

BNode * find_smallest(BNode * x)
{
    while(x->left != NULL)
    {
        x = x->left;
    }
    return x;
}
