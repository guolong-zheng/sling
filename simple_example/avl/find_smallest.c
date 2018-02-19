#include "avl.h"

int main(){
    AVLNode * root = create_avl(5);
    int res = avl_find_smallest(root);

    return 0;
}
