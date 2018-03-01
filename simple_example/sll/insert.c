#include "header.h"
#include <stdio.h>

SNnode * sll_insert(SNnode * x, int k)
{
    //pre
	if (x == NULL) {
		SNnode * leaf = (SNnode *) malloc(sizeof(SNnode));
		leaf->key = k;
		leaf->next = NULL;
        //post
		return leaf;
	} else if (k > x->key) {
		SNnode * tmp = sll_insert(x->next, k);
		x->next = tmp;
        //post
		return x;
	}	else {
		SNnode * new_root = (SNnode *) malloc(sizeof(SNnode));
		new_root->key = k;
		new_root->next = x;
        //post
		return new_root;
	}
}

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_sll(size);

    SNnode * res;
    res = sll_insert(root, (int)rand());

    return 0;
}
