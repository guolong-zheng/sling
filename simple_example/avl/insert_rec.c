#include "avl.h"

int main(){
    AVLNode * root = create_avl(5);
    AVLNode * res = avl_insert(root, (int)rand());

    return 0;
}
