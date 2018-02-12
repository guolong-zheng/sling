#include "sll.h"
#include <stdio.h>

int main(){
    SNnode * root = create_sll(5);

    int res = sll_find(root, (int)rand());

    return 0;
}
