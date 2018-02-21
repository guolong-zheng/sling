#include "g_slist.h"

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
  ) ;
*/
// ------------------------------------------------

Node * g_slist_reverse(Node * list)
  /*D_requires list^(list) */
  /*D_ensures  (list^(ret) & (old(keys^(list)) s= keys^(ret))) */
{
	Node * prev = NULL;
	while(list != NULL)
    /*D_invariant ((list^(list) * list^(prev)) & (old(keys^(list)) s= (keys^(list) union keys^(prev)))) */
	{

		Node * next = list->next;
		list->next = prev;
		prev = list;
		list = next;
	}
	return prev;
}

int main(){
    Node * root = create_list(5);
    Node * res = g_slist_reverse(root);

    return 0;
}
