#include "sll.h"
#include <stdio.h>

int main(){
    SNnode * root = create_sll(5);

    root = sll_delete_all(root, 2);

    return 0;
}
