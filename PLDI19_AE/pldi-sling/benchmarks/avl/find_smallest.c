#include "header.h"
#include <stdlib.h>
#include <stdio.h>

int avl_find_smallest(AVLNode * x)
{
	//pre
	if (x->left == NULL) {
		//post
		return x->key;
	} else {
		int r = avl_find_smallest(x->left);
		//post
		return r;
	}
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    AVLNode * root = create_avl(size);

    int res = avl_find_smallest(root);

    return 0;
}
