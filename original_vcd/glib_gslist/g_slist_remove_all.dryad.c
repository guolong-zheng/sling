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
  ) ;*/
// ------------------------------------------------  

_(dryad)
Node * g_slist_remove_all(Node * list, int data)
	/*D_requires list^(list) */
  /*D_ensures  (list^(ret) & (keys^(ret) s= (keys^(list) setminus (singleton data)))) */
{
	Node *tmp, *prev = NULL;
	tmp = list;
  int tp;

	while(tmp != NULL)
    /*D_invariant ((((~ (data i-in keys^(tmp))) => (keys^(list) s= (old(keys^(list)) setminus (singleton data)))) 
                      & list^(list)) 
                  & (((prev l= nil) & (tmp l= list)) 
                      | (((lseg^(list, prev) & (~ (data i-in lseg-keys^(list, prev)))) 
                          * ((prev |-> loc next: tmp; int key: tp) & (~ (data i= tp)))) 
                        * list^(tmp)))) */
	{
		if (tmp->key == data)
		{
			Node * tmp_next = tmp->next;
			if (prev != NULL) {
        tp = prev->key;
				prev->next = tmp_next;
			} else {
				list = tmp_next;
			}
			free(tmp);
			tmp = tmp_next;
		} else {
			prev = tmp;
			tmp = prev->next;
		}
	}
	return list;
}

