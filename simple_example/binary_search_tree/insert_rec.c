#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    BNode * root = create_tree(5);
    root = bst_insert_rec(root, (int)rand());

    return 0;
}
