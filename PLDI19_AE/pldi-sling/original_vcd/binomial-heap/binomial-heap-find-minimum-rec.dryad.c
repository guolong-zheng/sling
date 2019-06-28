// ---- Commmon definitions for binomial-heap examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef 
/*D_tag node */
struct node {
  int key;
  int order;
  struct node * children;
  struct node * sibling;
} SNnode;

/*D_defs
 define pred binomial-heap^(x):
 ( ((x l= nil) & emp) |
 (
 (x |-> loc children: chld; loc sibling: sbl; int key: ky; int order: odr) *
 ((
 (binomial-heap^(sbl) & ((orders^(sbl) set-lt odr) * true)) *
 ((binomial-heap^(chld) & (ky le-set keys^(chld))) &
 (((full-list^(chld) & ((length^(chld) + 1) i= odr)) & (orders^(chld) set-lt odr)) * true)
 )
 ) & (0 < odr))
 )
 ) ;
 
 define set-fun keys^(x):
 (case (x l= nil): emptyset;
 case ((x |-> loc children: chld2; loc sibling: sbl2; int key: ky2) * true):
 ((singleton ky2) union (keys^(chld2) union keys^(sbl2)));
 default: emptyset
 ) ;
 
 define set-fun orders^(x):
 (case (x l= nil): emptyset;
 case ((x |-> loc sibling: sbl3; int order: odr3) * true):
 ((singleton odr3) union orders^(sbl3));
 default: emptyset
 ) ;
 
 define pred full-list^(x):
 ( ((x l= nil) & emp) |
 (
 (x |-> loc sibling: sbl4; int order: odr4) *
 (
 full-list^(sbl4) & ((length^(sbl4) + 1) i= odr4)
 )
 )
 ) ;
 
 define int-fun length^(x):
 (case (x l= nil): 0;
 case ((x |-> loc sibling: sbl5) * true):
 (length^(sbl5) + 1);
 default: 0
 ) ;
*/
// ---------------------------------------------------------

_(dryad)
int binomial_heap_find__minimum_rec(SNnode * x)
  /*D_requires ((~ (x l= nil)) & binomial-heap^(x)) */
  /*D_ensures (((ret le-set old(keys^(x))) & (ret i-in old(keys^(x)))) & ((binomial-heap^(x) & (keys^(x) s= old(keys^(x)))) & ((orders^(x) s= old(orders^(x))) * true))) */
{
    SNnode * xs = x->sibling;
    int xk = x->key;
    
	if (xs == NULL) {
		return xk;
	} else {
		int y = binomial_heap_find__minimum_rec(xs);
        if (xk <= y) return xk;
        else          return y;
	}
}
