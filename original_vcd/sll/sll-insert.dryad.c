// ---- Commmon definitions for singly-linked list examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef 
/*D_tag node */
struct node {
  int key;
  struct node * next;
} SNnode;

/*D_defs
define pred sll^(x): 
  ( 
  ((x l= nil) & emp) | 
  ((x |-> loc next: nxt) * sll^(nxt))  
  ) ;
  
define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union keys^(nxt));
   default: emptyset
  ) ;*/
// --------------------------------------------------------------

_(dryad)
SNnode * sll_insert(SNnode * x, int k)
  /*D_requires sll^(x) */
  /*D_ensures (sll^(ret) & (keys^(ret) s= (old(keys^(x)) union (singleton k)))) */
{
	if (x == NULL) {
		SNnode * leaf = (SNnode *) malloc(sizeof(SNnode));
		_(assume leaf != NULL)

		leaf->key = k;
		leaf->next = NULL;
		return leaf;

	} else if (k > x->key) {
		SNnode * tmp = sll_insert(x->next, k);
		x->next = tmp;
		return x;
	}	else {	
		SNnode * new_root = (SNnode *) malloc(sizeof(SNnode));
		_(assume new_root != NULL)

		new_root->key = k;
		new_root->next = x;
		return new_root;
	}
}


