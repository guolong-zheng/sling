#include <stdlib.h>
#include "header.h"
#include <stdio.h>

int postorder(TNode * x, int n)
{
    //pre
	if (x == NULL) {
        //post
		return n;
	} else {
		int n1 = postorder(x->left, n);
		int n2 = postorder(x->right, n1);
		x->key = n2;
		int n3 = n2 + 1;
        //post
		return n3;
	}
}

int main(int argc, char * argv[]){
	int size = 0;
	sscanf(argv[1],"%d", &size);
    TNode * root = create_tree(size);

    int res = postorder(root, 0);
	postorder(NULL, 0);
    return 0;
}
