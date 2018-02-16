#include "binary_tree.h"

int main(){
    BNode * root = create_tree(5);
    root = bst_remove_root_rec(root);

    return 0;
}
