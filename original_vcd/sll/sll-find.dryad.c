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
int sll_find(SNnode * x, int k)
  /*D_requires sll^(x) */
  /*D_ensures ((sll^(x) & (keys^(x) s= old(keys^(x)))) & ((ret i= 1) <=> (k i-in old(keys^(x))))) */
{
	if (x == NULL) {
		return -1;
	} else if (k == x->key) {
		return 1;
	}	else {
    SNnode * x_next = x->next;
		int res = sll_find(x_next, k);
		return res;
	}	
}
