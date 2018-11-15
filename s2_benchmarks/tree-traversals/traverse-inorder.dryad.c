

typedef
/*D_tag t_node */
struct t_node {
  struct t_node * left;
  struct t_node * right;
  int key;
} TNode;

int inorder(TNode * x, int n)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
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
