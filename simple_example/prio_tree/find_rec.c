#include "prio_tree.h"

int main(){
    BNode * root = create_tree(5);
    BNode * res = treap_find_rec(root, (int)rand());

    return 0;
}
