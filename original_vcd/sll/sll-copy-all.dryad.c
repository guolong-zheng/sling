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
SNnode * sll_copy(SNnode * x, int k)
  /*D_requires sll^(x) */
  /*D_ensures ((sll^(ret) & (keys^(ret) s= old(keys^(x)))) * (sll^(x) & (keys^(x) s= old(keys^(x))))) */
{
	if (x == NULL) {
		return x;
	} else {
		SNnode * tmp = sll_copy(x->next, k);
		SNnode * new_node = (SNnode *) malloc(sizeof(SNnode));
		_(assume new_node != NULL)
    int tmp_key = x->key;
		new_node->key = tmp_key;
		new_node->next = tmp;
		return new_node;
	}
}

