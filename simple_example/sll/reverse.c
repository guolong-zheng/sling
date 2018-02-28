#include "sll.h"
#include <stdio.h>

SNnode * sll_reverse(SNnode * x)
{
    //pre
	SNnode * y = NULL;
	while (x != NULL)
    {
        //loopinv
		SNnode * tmp = x->next;
		x->next = y;
		y = x;
		x = tmp;
	}
    //post
	return y;
}

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_sll(size);

    SNnode * res;
    res = sll_reverse(root);
    return 0;
}
