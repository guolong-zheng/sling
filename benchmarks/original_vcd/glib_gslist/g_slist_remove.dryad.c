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
  )
  axiom: (lseg^(x, x) * (((x l= nil) & (length^(x) i= 0)) | ((~ (x l= nil)) & (0 < length^(x)))));
  

define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union keys^(nxt));
   default: emptyset
  ) ;

define int-fun length^(x):
  (case (x l= nil): 0;
   case ((x |-> loc next: nxt; int key: ky) * true): 
    (1 + length^(nxt));
   default: 0
  ) ;

define relation lseg^(head, tail): 
  ( 
  (((head l= tail) | ((head l= nil) & (tail l= nil))) & emp) | 
          ((head |-> loc next: nxt; int key: ky) * lseg^(nxt, tail))  
  ) 
axiom: ( 
      ((((head l= tail) => (emp & ((lseg-length^(head, tail) i= 0) & (lseg-keys^(head, tail) s= emptyset)))) &
      ((tail l= nil) => (list^(head) & ((length^(head) i= lseg-length^(head, tail)) & (keys^(head) s= lseg-keys^(head, tail)))))) &
      (list^(tail) -* (list^(head) & ((keys^(head) s= (lseg-keys^(head, tail) union keys^(tail))) & (length^(head) i= (lseg-length^(head, tail) + length^(tail))))))) &
      (((tail |-> loc next: virtual tn; int key: virtual tk) * list^(tn)) -* ((lseg^(head, tn) & ((lseg-keys^(head, tn) s= (lseg-keys^(head, tail) union (singleton tk))) & (lseg-length^(head, tn) i= (lseg-length^(head, tail) + 1))) ) * list^(tn)))
     ) ;

define bin-set-fun lseg-keys^(head, tail):
  (case ((head l= tail) | ((head l= nil) & (tail l= nil))) : emptyset;
   case ((head |-> loc next: nxt; int key: ky) * true): 
    ((singleton ky) union lseg-keys^(nxt, tail));
   default: emptyset
  ) ;

define bin-int-fun lseg-length^(head, tail):
  (case (head l= tail) : 0;
   case ((head |-> loc next: nxt; int key: ky) * true): 
    (1 + lseg-length^(nxt, tail));
   default: 0
  ) ;
*/
// ------------------------------------------------

_(dryad)
Node * g_slist_remove (Node * list, int data _(ghost Node * y) _(ghost Node * z))
  /*D_requires (list^(list) 
                & ((~ (data i-in keys^(list))) 
                  | (((lseg^(list, y) & (~ (data i-in lseg-keys^(list, y)))) * (y |-> loc next: z; int key: data)) 
                    * list^(z)))) */
  /*D_ensures (list^(ret) 
                & (((~ (data i-in old(keys^(list))) => (keys^(ret) s= old(keys^(list))) 
                  & ((data i-in old(keys^(list)) => (lseg^(ret, z) * list^(z))))) */
{
	Node *tmp;
  Node *prev = NULL;
	tmp = list;
  int tp;

	while(tmp != NULL)
  /*D_invariant ((old(keys^(list)) s= keys^(list)) 
                 & ((((prev l= nil) & (tmp l= list)) & list^(list)) 
                  | ((((lseg^(list, prev) & (~ (data i-in lseg-keys^(list, prev)))) 
                          * ((prev |-> loc next: tmp; int key: tp) & (~ (data i= tp)))) 
                        * (lseg^(tmp, y) & (~ (data i-in lseg-keys^(tmp, y))))) 
                    * ((y |-> loc next: z; int key: data) * list^(z))))) */
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
			break;
		}
		
		prev = tmp;
		tmp = prev->next;

	}
	return list;
}

