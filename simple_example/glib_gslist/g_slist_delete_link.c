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

Node * g_slist_delete_link(Node * list, Node * link_)
  /*D_requires (list^(list) & (((~ (link l= nil)) & lseg^(list, link)) * true)) */
  /*D_ensures ((list^(ret) & (~ (link l-in reachnodes^(ret)))) * ((link |-> loc next: z) & (z l= nil))) */
{
	list = g_slist_remove_link(list, link_);
	free(link_);
	return list;
}

int main(){
    Node * list = create_list(5);
    Node * link_ = list->next;
    Node * res = g_slist_delete_link(list, link_);

    return 0;
}
