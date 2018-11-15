
#include <stdlib.h>

typedef 
/*D_tag node */
struct node {
  int key;
  int order;
  struct node * children;
  struct node * sibling;
} SNnode;

int binomial_heap_find__minimum_rec(SNnode * x)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
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
