#include "sll.h"
#include <stdio.h>

int main(){
    SNnode * nodes[5];
    for(int i = 0; i < 5; i++){
        nodes[i] = node_create(i);
    }

    SNnode * root = NULL;
    for(int i = 0; i < 5; i++){
        root = sll_append(root, nodes[i]);
    }

    while(root != NULL){
        root = root->next;
    }

    return 0;
}
