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

Node * g_slist_copy(Node * list)
  /*D_requires list^(x) */
  /*D_ensures ((list^(old(x)) & (old(keys^(x)) s= keys^(old(x)))) * (list^(ret) & (old(keys^(x)) s= keys^(ret)))) */
{
	Node * new_list = NULL;
	if (list != NULL) {
		Node * last = NULL;

		new_list = (Node *) malloc(sizeof(Node));
        int list_key = list->key;
		new_list->key = list_key;
		new_list->next = NULL;

		last = new_list;

		list = list->next;

		while(list != NULL)
      /*D_invariant (((list^(old(list)) & (old(keys^(list)) s= keys^(old(list))))
                      * (list^(new_list) & (lseg^(new_list, last)
                      * ((last |-> loc next: u; int key: d) & (u l= nil)))))
                     & ((old(keys^(list)) s= (keys^(new_list) union keys^(list))) * true)) */

		{
			Node * tail = (Node *)malloc(sizeof(Node));
            int list_key = list->key;
 			tail->key = list_key;
			tail->next = NULL;

			last->next = tail;
			last = last->next;

			list = list->next;
		}
	}

	return new_list;
}

int main(){
    Node * root = create_list(5);
    Node * res = g_slist_copy(root);

    return 0;
}
