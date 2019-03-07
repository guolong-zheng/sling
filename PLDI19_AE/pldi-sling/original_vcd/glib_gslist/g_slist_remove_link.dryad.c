// ---- Definitions for glib/gslist examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} Node;

/*D_defs
define pred list^(x): 
  ( 
  ((x l= nil) & emp) | 
          ((x |-> loc next: nxt; int key: ky) * list^(nxt))
  ) ;
  
define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union keys^(nxt));
   default: emptyset
  ) ;


define lset-fun reachnodes^(x):
  (case (x l= nil): emptylset;
   case ((x |-> loc next: nxt; int key: ky) * true): 
    ((lsingleton x) lunion reachnodes^(nxt));
   default: emptylset
  ) ;


define relation lseg^(head, tail): 
  ( 
  (((head l= tail) | ((head l= nil) & (tail l= nil))) & emp) | 
          ((head |-> loc next: nxt; int key: ky) * lseg^(nxt, tail))  
  ) 
axiom: ( 
      (list^(tail) -* (list^(head) & (keys^(head) s= (lseg-keys^(head, tail) union keys^(tail))))) &
      (((tail |-> loc next: virtual tn; int key: virtual tk) * list^(tn)) -* ((lseg^(head, tn) & (lseg-keys^(head, tn) s= (lseg-keys^(head, tail) union (singleton tk)))) * list^(tn))) 
     ) ;

define bin-set-fun lseg-keys^(head, tail):
  (case ((head l= tail) | ((head l= nil) & (tail l= nil))) : emptyset;
   case ((head |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union lseg-keys^(nxt, tail));
   default: emptyset
  ) ;
*/
// ------------------------------------------------

_(dryad)
Node * g_slist_remove_link(Node * list, Node * link _(ghost Node * z))
  /*D_requires (list^(list) & (((~ (link l= nil)) & lseg^(list, link)) * true)) */
  /*D_ensures (list^(ret) * ((link |-> loc next: z) & (z l= nil))) */
{
	Node * tmp;
	Node * prev;
  int tp;

	prev = NULL;
	tmp = list;

	while(tmp != NULL)
    /*D_invariant 
      ((list^(list) & (((~ (link l= nil)) & lseg^(list, link)) * true)) 
      & (((prev l= nil) & (list l= tmp)) 
        | (((lseg^(list, prev) * (prev |-> loc next: tmp; int key: tp)) * lseg^(tmp, link)) * list^(link))))
    */
	{
		if (tmp == link)
		{
			Node * tmp_next = tmp->next;
			if (prev != NULL) {
        tp = prev->key;
				prev->next = tmp_next;

			} else {
				list = tmp_next;
			}
			tmp->next = NULL;
			break;	
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return list;
}

