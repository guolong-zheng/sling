// ---- Commmon definitions for sorted list examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} SNnode;

/*D_defs
define pred sorted^(x): 
  ( 
  ((x l= nil) & emp) | 
          ((x |-> loc next: nxt; int key: ky) * 
      (sorted^(nxt) & (ky lt-set keys^(nxt)))
      )  
  ) ;
  
define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union keys^(nxt));
   default: emptyset
  ) ;
*/
// -------------------------------------------------------

_(dryad)
int sorted_find(SNnode * l, int k)
  /*D_requires sorted^(x) */
  /*D_ensures ((sorted^(x) & (keys^(x) s= old(keys^(x)))) & ((ret i= 1) <=> (k i-in old(keys^(x))))) */
{
	if (l == NULL) {
		return -1;
	} else if (l->key == k) {
		return 1;
	} else {
		int res = sorted_find(l->next, k);
		return res;
	}
}

