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
define pred sll^(x): 
  ( 
  ((x l= nil) & emp) | 
          ((x |-> loc next: nxt; int key: ky) * sll^(nxt))  
  )
  axiom: (lseg^(x, x) * (((x l= nil) & (keys^(x) s= emptyset)) | ((~ (x l= nil)) & (~ (keys^(x) s= emptyset)))));

define pred sorted-sll^(x): 
  ( 
  ((x l= nil) & emp) | 
          ((x |-> loc next: nxt; int key: ky) * 
      (sorted-sll^(nxt) & (ky le-set keys^(nxt)))
      )  
  )
  axiom: (sorted-lseg^(x, x) * sll^(x));
  
define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union keys^(nxt));
   default: emptyset
  ) ;

define relation lseg^(head, tail): 
  ( 
  ((head l= tail) & emp) | 
          ((head |-> loc next: nxt; int key: ky) * (lseg^(nxt, tail) & (ky le-set lseg-keys^(nxt, tail))))  
  ) 
  axiom: ( (((head l= tail) => (emp & (lseg-keys^(head, tail) s= emptyset))) & ((tail l= nil) => (sll^(head) & (keys^(head) s= lseg-keys^(head, tail))))) &
  ( (sll^(tail) -* (sll^(head) & (keys^(head) s= (lseg-keys^(head, tail) union keys^(tail))))) &
    (((tail |-> loc next: virtual tn; int key: virtual tk) * sll^(tn)) -* ((lseg^(head, tn) & (lseg-keys^(head, tn) s= (lseg-keys^(head, tail) union (singleton tk)))) * sll^(tn))) ) ) ;

define relation sorted-lseg^(head, tail): 
  ( 
  ((head l= tail) & emp) | 
          ((head |-> loc next: nxt; int key: ky) * (sorted-lseg^(nxt, tail) & (ky le-set lseg-keys^(nxt, tail))))  
  ) 
  axiom: ( lseg^(head, tail) &
    ( ((tail l= nil) => sorted-sll^(head)) &
  ( (sorted-sll^(tail) -* ((lseg-keys^(head, tail) le keys^(tail)) => sorted-sll^(head))) &
    (((tail |-> loc next: virtual tn; int key: virtual tk) * sll^(tn)) -* (((lseg-keys^(head, tail) set-le tk) * true) => (sorted-lseg^(head, tn) * sll^(tn)))) ) ) ) ;

define bin-set-fun lseg-keys^(head, tail):
  (case (head l= tail) : emptyset;
   case ((head |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union lseg-keys^(nxt, tail));
   default: emptyset
  ) ;*/
// -------------------------------------------------------

_(dryad)
SNnode * concat_sorted(SNnode * l1, SNnode * l2)
  /*D_requires (sorted-sll^(l1) * sorted-sll^(l2)) */
  /*D_ensures  (sorted-sll^(ret) & (keys^(ret) s= (old(keys^(l1)) union old(keys^(l2))))) */
;

_(dryad)
SNnode * quick_sort(SNnode * l)
  /*D_requires sll^(l) */
  /*D_ensures (sorted-sll^(ret) & (keys^(ret) s= old(keys^(l)))) */ 
{

	if (l == NULL) {
		return l;
	} 

	SNnode * curr = l->next;

	int pivot = l->key;
	l->next = NULL;

	SNnode * lpt = NULL;
	SNnode * rpt = NULL;

	SNnode * tmp = curr;

	while(curr != NULL)
    /*D_invariant (l |-> loc next: NULL; int key: pivot) * 
       ((sll^(curr) * ((sll^(lpt) & (keys^(lpt) set-le pivot)) 
          * (sll^(rpr) & (pivot le-set keys^(rpt))))) & 
       (((keys^(curr) union (keys^(lpt) union keys^(rpt))) union (singleton pivor)) s= old(keys^(l)))) */
	{
		tmp = curr->next;
		if (curr->key <= pivot) {
			curr->next = lpt;
			lpt = curr;
		} else {		
			curr->next = rpt;
			rpt = curr;
		}
		curr = tmp;
	}

	l->next = rpt;
	
	SNnode * t2 = quick_sort(l);

	if (lpt == NULL) {
		return t2;
	}
	SNnode * t1 = quick_sort(lpt);
	return concat_sorted(t1, t2);
}
