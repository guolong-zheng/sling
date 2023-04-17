#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int sll_find(SNnode * x, int k)
{
    //pre
	if (x == NULL) {
        //post
		return -1;
	} else if (k == x->key) {
        //post
		return 1;
	} else {
        SNnode * x_next = x->next;
		int res = sll_find(x_next, k);
        //post
		return res;
	}
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);
	sll_find(NULL, 1);
	int i;
    SNnode * root = NULL;
    for(i = 0; i < size; i++){
		SNnode * node = (SNnode *)malloc(sizeof(SNnode));
	    node->key = i;
	    node->next = root;
		root = node;
    }
	sll_find(root, 2);
	SNnode * l1 = create_sll(size);
    sll_find(l1, rand());
    return 0;
}
