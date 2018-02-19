#include <stdlib.h>

typedef struct b_node {
  struct b_node * left;
  struct b_node * right;
  int key;
} BNode;

typedef struct l_node {
  struct l_node * next;
  int key;
} LNode;

LNode * tree2list_rec(BNode * t, LNode * l)
{

	if (t == NULL) {
		return l;
	} else {

		LNode * lnode = (LNode *) malloc(sizeof(LNode));
		_(assume lnode != NULL)

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
