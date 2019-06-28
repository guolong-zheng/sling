// ---- Commmon definitions for sorted list examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} SNnode;

/* D_defs
define pred sorted^(x): 
  ( 
  ((x l= nil) & emp) | 
          ((x |-> loc next: nxt; int key: ky) * 
      (sorted^(nxt) & (ky lt-set keys^(nxt)))
      )  
  ) ;

define pred revsorted^(x): 
  ( 
  ((x l= nil) & emp) | 
          ((x |-> loc next: nxt; int key: ky) * 
      (revsorted^(nxt) & (keys^(nxt) set-lt ky))
      )  
  ) ;
  
define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union keys^(nxt));
   default: emptyset
  ) ; */
// -------------------------------------------------------

_(dryad)
SNnode * reverse_sorted(SNnode * l)
	/*D_requires sorted^(l)  */
  /*D_ensures  ((revsorted^(ret) * sorted^(l)) & ((keys^(ret) union keys^(l)) s= old(keys^(l)))) */
{
	SNnode * r = NULL;

	while(l != NULL)
    /*D_invariant ((revsorted^(r) * sorted^(l)) & ((keys^(r) union keys^(l)) s= old(keys^(l)))) */
	{
		SNnode * t = l->next;
		
		l->next = r;
		r = l;
		l = t;
	}
	return r;
}

