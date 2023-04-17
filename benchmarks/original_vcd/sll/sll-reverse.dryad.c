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
SNnode * sll_reverse(SNnode * x)
  /*D_requires sll^(x) */
  /*D_ensures (sll^(ret) & (keys^(ret) s= old(keys^(x)))) */
{
	SNnode * y = NULL;

	while (x != NULL)
    /*D_invariant ((sll^(x) * sll^(y)) & ((keys^(x) union keys^(y)) s= old(keys^(x)))) */
	{
		SNnode * tmp = x->next;
		x->next = y;
		y = x;
		x = tmp;
	}
	return y;
}
