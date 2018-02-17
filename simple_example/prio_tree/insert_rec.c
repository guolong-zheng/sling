#include "prio_tree.h"

int main(){
    BNode * root = create_tree(5);
    BNode * res = treap_insert_rec(root, (int)rand(),(int)rand());
    return 0;
}
