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
  ) ; */
// --------------------------------------------------------------

_(dryad)
SNnode * sll_append(SNnode * x1, SNnode * x2)
  /*D_requires (sll^(x1) * sll^(x2)) */
  /*D_ensures  (sll^(ret) & (keys^(ret) s= (old(keys^(x1)) union old(keys^(x2))))) */
{
	if (x1 == NULL) {
		return x2;
	} else {
		SNnode * tmp = sll_append(x1->next, x2);
		x1->next = tmp;
		return x1;
	}
	
}
