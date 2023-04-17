// ---- Commmon definitions for sorted list examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} SNnode;

/*
define pred sorted^(x): 
  ( 
  ((x l= nil) & emp) | 
          ((x |-> loc next: nxt; int key: ky) * 
      (sorted^(nxt) & (ky lt-set keys^(nxt)))
      )  
  ) ;

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
 // -------------------------------------------------------


SNnode * sorted_insert(SNnode *x, int k)
   /*D_requires (sll^(x) & sorted^(x)) */
   /*D_ensures ((sll^(ret) & sorted^(ret)) & (keys^(ret) s= (old(keys^(x)) union (singleton k)))) */
;

_(dryad)
SNnode * insertion_sort_copy(SNnode * l)
  /*D_requires sll^(l) */
  /*D_ensures ((sll^(ret) & sorted^(ret)) & (keys^(ret) s= old(keys^(l)))) */
{
	if (l == NULL) {
		return l;
	} else {
		SNnode * tl = insertion_sort_copy(l->next);

		SNnode * nl = sorted_insert(tl, l->key);
		return nl;
	}
}

