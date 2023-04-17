#include "header.h"
#include <stdio.h>
#include <stdlib.h>

SNnode * sorted_delete_all(SNnode * x, int k)
{
    //pre
	SNnode * rst = NULL;
	if (x == NULL) {
        rst = x;
	} else if (x->key == k) {
		SNnode * tmp = sorted_delete_all(x->next, k);
		free(x);
        rst = tmp;
	} else {
		SNnode * tmp = sorted_delete_all(x->next, k);
		x->next = tmp;
        rst = x;
		//return x;
	}
	//post
	return rst;
}

int main( int argc, char * argv[] ){
    int size;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_random(size);

    SNnode * res = sorted_delete_all(root, rand_num());
	sorted_delete_all(NULL, rand_num());
    return 0;
}
