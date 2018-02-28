#include "sll.h"
#include <stdio.h>

SNnode * sll_delete_all(SNnode * x, int k)
{
    //pre
	if (x == NULL) {
        //post
		return x;
	} else if (x->key == k) {
		SNnode * tmp = sll_delete_all(x->next, k);
		free(x);
        //post
		return tmp;
	} else {
		SNnode * tmp = sll_delete_all(x->next, k);
		x->next = tmp;
        //post
		return x;
	}
}

//multi situation
int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);

    SNnode * root = create_sll(size);

    root = sll_delete_all(root, 2);

    return 0;
}
