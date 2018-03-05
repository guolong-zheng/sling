#include "create_tree.h"
#include <stdlib.h>

int inorder(TNode * x, int n)
{
	//pre
	if (x == NULL) {
		//post
		return n;
	} else {
		int n1 = inorder(x->left, n);
		x->key = n1;
		int n2 = n1 + 1;
		int n3 = inorder(x->right, n2);
		//post
		return n3;
	}
}

int main(int argc, char * argv[]){
	int size = 0;
	sscanf(argv[1],"%d", &size);
    TNode * root = create_tree(size);

    int res = inorder(root, 0);

    return 0;
}
