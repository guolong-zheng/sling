
typedef
/*D_tag b_node */
struct b_node {
  struct b_node * left;
  struct b_node * right;
  int key;
} BNode;

typedef
/*D_tag l_node */
struct l_node {
  struct l_node * next;
  int key;
} LNode;

LNode * tree2list_rec(BNode * t, LNode * l)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	
	if (t == NULL) {
		return l;
	} else {

		LNode * lnode = (LNode *) malloc(sizeof(LNode));

		int tkey = t->key;

		lnode->key = tkey;
		lnode->next = NULL;
  
    BNode * tright = t->right;
		BNode * tleft = t->left;

		LNode * tmp_list1 = tree2list_rec(tright, l);

		lnode->next = tmp_list1;

		free(t);

		LNode * tmp_list2 = tree2list_rec(tleft, lnode);
		
		return tmp_list2;
	}
}
