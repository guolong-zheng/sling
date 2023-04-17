#include "header.h"
#include <stdio.h>
#include <stdlib.h>

SNnode * sorted_insert(SNnode *x, int k)
{
    //pre
	SNnode * ret;
	if (x == NULL) {
		SNnode * tail = (SNnode *) malloc(sizeof(SNnode));
		tail->key = k;
		tail->next = NULL;
        ret = tail;
		//return tail;
	}
	else if (k > x->key) {
		SNnode * tmp = sorted_insert(x->next, k);
		x->next = tmp;
        ret = x;
		//return x;
	}
	else {
		SNnode * head = (SNnode *) malloc(sizeof(SNnode));
		head->key = k;
		head->next = x;
        ret = head;
		//return head;
	}
	//post
	return ret;
}

int main( int argc, char * argv[] ){
    int size;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_sorted_list(0, MAX_RAND, size);

    SNnode * res = sorted_insert(root, rand_num());
    return 0;
}
