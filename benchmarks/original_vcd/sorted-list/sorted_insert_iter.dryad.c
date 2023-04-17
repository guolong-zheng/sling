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

define relation lseg^(head, tail): 
  ( 
  ((head l= tail) & emp) | 
          ((head |-> loc next: nxt; int key: ky) * (lseg^(nxt, tail) & (ky lt-set lseg-keys^(nxt, tail))))  
  ) 
  axiom: ( (sorted^(tail) -* ((lseg-keys^(head, tail) lt keys^(tail)) => (sorted^(head) & (keys^(head) s= (lseg-keys^(head, tail) union keys^(tail)))))) &
    (((tail |-> loc next: virtual tn; int key: virtual tk) * sorted^(tn)) -* (((lseg-keys^(head, tail) set-lt tk) * true) => ((lseg^(head, tn) & (lseg-keys^(head, tn) s= (lseg-keys^(head, tail) union (singleton tk)))) * sorted^(tn)))) ) ;

define bin-set-fun lseg-keys^(head, tail):
  (case (head l= tail) : emptyset;
   case ((head |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union lseg-keys^(nxt, tail));
   default: emptyset
  ) ;*/
// -------------------------------------------------------  

_(dryad)
SNnode * sorted_insert_iter(SNnode * l, int k)
  /*D_requires (sorted^(x) & (~ (k i-in keys^(x)))) */
  /*D_ensures  (sorted^(ret) & (keys^(ret) s= (keys^(x) union (singleton k)))) */
{
	if (l == NULL) {
		SNnode * tl = (SNnode *) malloc(sizeof(SNnode));
		_(assume tl != NULL)
		tl->key = k;
		tl->next = NULL;
		return tl;
	} else {
		if (k <= l->key) {

			SNnode * hd = (SNnode *) malloc(sizeof(SNnode));
			_(assume hd != NULL)

			hd->key = k;
			hd->next = l;

			return hd;
			
		} else {

			SNnode * prev = l;
			SNnode * next = l->next;

			while(next != NULL && k > next->key) 
        /*D_invariant ( ((sorted^(next) & ((prevk lt-set keys^(next)) & (~ (k i-in keys^(next))))) 
                     * ((prev |-> loc next: next; int key: prevk) & (prevk < k))) 
                     * (lseg^(x, prev) & (lseg-keys^(x, prev) set-lt prevk)) )  */
			{
				prev = next;
				next = next->next;
			}

			SNnode * curr = (SNnode *) malloc(sizeof(SNnode));
			_(assume curr != NULL)

			curr->key = k;
			curr->next = next;
			
			prev->next = curr;
			return l;
		}
	}
}