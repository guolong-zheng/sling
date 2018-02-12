#include "sll.h"
#include <stdio.h>

int main(){
    SNnode * root = create_sll(5);
    root = sll_reverse(root);
    return 0;
}
