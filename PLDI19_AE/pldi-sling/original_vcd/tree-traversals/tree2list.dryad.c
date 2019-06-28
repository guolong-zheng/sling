// ---- Definitions for tree traversal examples  ----
#include <vcc.h>
#include <stdlib.h>

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

/*D_defs
define pred sorted^(x): 
  ( 
  ((x l= nil) & emp) | 
          ((x |-> loc next: nxt; int value: ky) * 
      (sorted^(nxt) & (ky le-set list-keys^(nxt)))
      )  
  ) ;
  
define set-fun list-keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc next: nxt; int value: ky) * true): 
    ((singleton ky) union list-keys^(nxt));
   default: emptyset
  ) ;


define pred bst^(x): 
  ( ((x l= nil) & emp) |
    ((x |-> loc left: lft; loc right: rgt; int key: ky) 
    * ((bst^(lft) & (bst-keys^(lft) set-le ky)) 
    * (bst^(rgt) & (ky le-set bst-keys^(rgt)))))  
  );

define set-fun bst-keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc left: lft; loc right: rgt; int key: ky) * true): 
    ((singleton ky) union (bst-keys^(lft) union bst-keys^(rgt)));
   default: emptyset
  ) ;
*/

// --------------------------------------------------

_(dryad)
LNode * tree2list_rec(BNode * t, LNode * l)
  /*D_requires ((bst^(t) * sorted^(l)) & (bst-keys^(t) le list-keys^(l))) */
  /*D_ensures  (sorted^(ret) & (list-keys^(ret) s= (old(bst-keys^(t)) union old(list-keys^(l))))) */
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