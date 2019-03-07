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
SNnode * merge_sort_copy(SNnode * l1, SNnode * l2)
  /*D_requires (sorted^(l1) * sorted^(l2)) */
  /*D_ensures  (sorted^(ret) & (keys^(ret) s= (old(keys^(l1)) union old(keys^(l2))))) */
{

	if (l1 == NULL) {
		return l2;
	} else if (l2 == NULL) {
		return l1;
	} else {
		if (l1->key <= l2->key) {
			SNnode * tl = merge_sort_copy(l1->next, l2);
			SNnode * nl = (SNnode *) malloc(sizeof(SNnode));
      _(assume nl != NULL)
      int l1_key = l1->key;
			nl->key  = l1_key;
			nl->next = tl;
			return nl;	
		} else {
			SNnode * tl = merge_sort_copy(l1, l2->next);
			SNnode * nl = (SNnode *) malloc(sizeof(SNnode));
      _(assume nl != NULL)
      
      int l2_key = l2->key;
			nl->key = l2_key;
			nl->next = tl;

			return nl;
		}
	}
}
