#include "prio_tree.h"

int main(){
    BNode * root = create_tree(5);
    BNode * res = treap_remove_root_rec(root);

    return 0;
}
