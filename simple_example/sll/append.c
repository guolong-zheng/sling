#include "sll.h"
#include <stdio.h>

SNnode * sll_append(SNnode * x1, SNnode * x2);

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

int main(){
    SNnode * nodes[5];
    int i = 0;
    for(i = 0; i < 5; i++){
        nodes[i] = node_create(i);
    }

    SNnode * root = NULL;
    for(i = 0; i < 5; i++){

        root = sll_append(root, nodes[i]);

    }

    while(root != NULL){
        root = root->next;
    }

    return 0;
}
