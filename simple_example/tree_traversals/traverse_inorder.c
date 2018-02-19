#include "create_tree.h"
#include <stdlib.h>

int inorder(TNode * x, int n)
{
	if (x == NULL) {
		return n;
	} else {
		int n1 = inorder(x->left, n);
		x->key = n1;
		int n2 = n1 + 1;
		int n3 = inorder(x->right, n2);
		return n3;
	}
}

int main(){
    TNode * root = create_tree(5);
    get_key(root, 0);

    int res = inorder(root, (int)rand());

    return 0;
}
