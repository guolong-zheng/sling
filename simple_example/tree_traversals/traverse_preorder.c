#include "header.h"
#include <stdlib.h>

int preorder(TNode * x, int n)
{
    //pre
	if (x == NULL) {
        //post
		return n;
	} else {
		x->key = n;
		int n1 = n + 1;
		int n2 = preorder(x->left, n1);
		int n3 = preorder(x->right, n2);
        //post
		return n3;
	}
}

int main(int argc, char * argv[]){
	int size = 0;
	sscanf(argv[1],"%d", &size);
    TNode * root = create_tree(size);

    int res = preorder(root, 0);

    return 0;
}
