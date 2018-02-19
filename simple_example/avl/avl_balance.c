#include "avl.h"

int main(){
    AVLNode * root = create_avl(5);
    AVLNode * res = avl_balance(root);

    return 0; 
}
