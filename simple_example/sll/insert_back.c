#include "header.h"
#include <stdio.h>
#include <stdlib.h>

SNnode * sll_insert_back(SNnode * x, int k)
{
    //pre
	if (x == NULL) {
		SNnode * tail = (SNnode *) malloc(sizeof(SNnode));
		tail->key  = k;
		tail->next = NULL;
        //post
		return tail;
	} else {
		SNnode * tmp = sll_insert_back(x->next, k);
		x->next = tmp;
        //post
		return x;
	}
}

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_sll(size);

    SNnode * res;
    res = sll_insert_back(root, (int)rand());

    return 0;
}
