#include "sll.h"
#include <stdio.h>

int main(){
    SNnode * root = create_sll(5);
    SNnode * x = sll_copy(root, (int)rand());
    return 0;
}
