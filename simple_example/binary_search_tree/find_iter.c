#include "binary_tree.h"

int main(){
    BNode * root = create_tree(5);
    BNode * res = bst_find_iter(root, (int)rand());

    return 0;
}
