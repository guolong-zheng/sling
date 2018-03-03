#include "avl.h"
#include <stdlib.h>

int avl_find_smallest(AVLNode * x)
{
	if (x->left == NULL) {
		return x->key;
	} else {
		int r = avl_find_smallest(x->left);
		return r;
	}
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argc, "%d", &size);
    AVLNode * root = create_avl(size);

    int res = avl_find_smallest(root);

    return 0;
}
