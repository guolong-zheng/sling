#include "sll.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    SNnode * root = create_sll(5);

    root = sll_insert_back(root, (int)rand());

    return 0;
}
