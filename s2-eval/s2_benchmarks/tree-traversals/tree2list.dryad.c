#include "stdhipmem.h"



struct l_node * tree2list_rec(struct b_node * t, struct l_node * l)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	
	if (t == NULL) {
		return l;
	} else {

		struct l_node * lnode = (struct l_node *) malloc(sizeof(struct l_node));

		int tkey = t->key;

		lnode->key = tkey;
		lnode->next = NULL;
  
    struct b_node * tright = t->right;
		struct b_node * tleft = t->left;

		struct l_node * tmp_list1 = tree2list_rec(tright, l);

		lnode->next = tmp_list1;

		freel(t);

		struct l_node * tmp_list2 = tree2list_rec(tleft, lnode);
		
		return tmp_list2;
	}
}
