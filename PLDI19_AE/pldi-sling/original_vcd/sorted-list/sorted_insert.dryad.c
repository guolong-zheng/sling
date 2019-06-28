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
  ) ;*/
// -------------------------------------------------------

_(dryad)
SNnode * sorted_insert(SNnode *x, int k)
   /*D_requires sorted^(x) */
   /*D_ensures (sorted^(ret) & (keys^(ret) s= (old(keys^(x)) union (singleton k)))) */
{

	if (x == NULL) {
		SNnode * tail = (SNnode *) malloc(sizeof(SNnode));
		_(assume tail != NULL)

		tail->key = k;
		tail->next = NULL;

		return tail;
	} 
	else if (k > x->key) {
		SNnode * tmp = sorted_insert(x->next, k);
		x->next = tmp;
		return x;
	} 
	else {

		SNnode * head = (SNnode *) malloc(sizeof(SNnode));
		_(assume head != NULL)

		head->key = k;
		head->next = x;

		return head;
	}
}

