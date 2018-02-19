#include <stdlib.h>

typedef struct t_node {
  struct t_node * left;
  struct t_node * right;
  int key;
} TNode;

int postorder(TNode * x, int n)
{

	if (x == NULL) {
		return n;
	} else {
		int n1 = postorder(x->left, n);
		int n2 = postorder(x->right, n1);
		x->key = n2;
		int n3 = n2 + 1;
		return n3;
	}
}
