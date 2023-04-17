#include "header.h"
#include <stdlib.h>
#include <stdio.h>

int binomial_heap_find__minimum_rec(SNnode * x)
{
    //pre
    SNnode * xs = x->sibling;
    int xk = x->key;

	if (xs == NULL) {
        //post
		return xk;
	} else {
		int y = binomial_heap_find__minimum_rec(xs);
        if (xk <= y)
            //post
            return xk;
        else
            //post
            return y;
	}
}


int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    SNnode * x = NULL;
    x = create_heap(size);

    int res = binomial_heap_find__minimum_rec(x);
}
