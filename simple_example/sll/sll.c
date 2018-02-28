#include "sll.h"
#include <stdio.h>
#include <stdlib.h>

SNnode * create_node()
{
    SNnode * node = (SNnode *)malloc(sizeof(SNnode));
    node->key = rand() % (2*MAX_RAND) - MAX_RAND;
    node->next = NULL;
    return node;
}

SNnode * create_sll(int size){
    int i;
    SNnode * root = NULL;
    for(i = 0; i < size; i++){
        root = sll_append(root, create_node());
    }

    return root;
}

SNnode * sll_append(SNnode * x1, SNnode * x2)
{
	    //pre
        if (x1 == NULL) {
		//post
                return x2;
        } else {
                SNnode * tmp = sll_append(x1->next, x2);
                x1->next = tmp;
		//post
                return x1;
        }
}
