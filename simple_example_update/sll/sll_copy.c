#include "header.h"
#include <stdio.h>
#include <stdlib.h>

SNnode * sll_copy(SNnode * x, int k)
{
  //pre
	if (x == NULL) {
    //post
		return x;
	} else {
		SNnode * tmp = sll_copy(x->next, k);
		SNnode * new_node = (SNnode *) malloc(sizeof(SNnode));
    	int tmp_key = x->key;
		new_node->key = tmp_key;
		new_node->next = tmp;
    //post
		return new_node;
	}
}

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_sll(size);

    SNnode * r;
    r = sll_copy(root, (int)rand());
	sll_copy(NULL,(int)rand());
    return 0;
}
