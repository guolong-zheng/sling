#include "header.h"
#include <stdio.h>

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

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_sll(size);

    int res = sll_find(root, (int)rand());

    return 0;
}
