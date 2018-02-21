#include "g_slist.h"

/*D_defs
define pred list^(x):
  (
  ((x l= nil) & emp) |
          ((x |-> loc next: nxt; int key: ky) * list^(nxt))
  )
  axiom: (lseg^(x, x) * (((x l= nil) & (length^(x) i= 0)) | ((~ (x l= nil)) & (0 < length^(x)))));

define pred sorted-list^(x):
  (
  ((x l= nil) & emp) |
          ((x |-> loc next: nxt; int key: ky) * (sorted-list^(nxt) & (ky lt-set keys^(nxt))))
  )
axiom: ((list^(x) & (sorted-lseg^(x, x) * (((x l= nil) & (length^(x) i= 0)) | ((~ (x l= nil)) & (0 < length^(x)))))) &
      (((x |-> int key: tk) * true) => (tk lt-set keys^(x)))
     );

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

define relation sorted-lseg^(head, tail):
  (
  (((head l= tail) | ((head l= nil) & (tail l= nil))) & emp) |
          ((head |-> loc next: nxt; int key: ky) * (sorted-lseg^(nxt, tail) & (ky lt-set lseg-keys^(nxt, tail))))
  )
axiom: (
      ((((head l= tail) => (emp & ((lseg-length^(head, tail) i= 0) & (lseg-keys^(head, tail) s= emptyset)))) &
      ((tail l= nil) => (sorted-list^(head) & ((length^(head) i= lseg-length^(head, tail)) & (keys^(head) s= lseg-keys^(head, tail)))))) &
      (sorted-list^(tail) -* ((lseg-keys^(head, tail) le keys^(tail)) => (sorted-list^(head) & ((keys^(head) s= (lseg-keys^(head, tail) union keys^(tail))) & (length^(head) i= (lseg-length^(head, tail) + length^(tail)))))))) &
      (((tail |-> loc next: virtual tn; int key: virtual tk) * list^(tn)) -* (((lseg-keys^(head, tail) set-lt tk) => (sorted-lseg^(head, tn) & ((lseg-keys^(head, tn) s= (lseg-keys^(head, tail) union (singleton tk))) & (lseg-length^(head, tn) i= (lseg-length^(head, tail) + 1))) )) * list^(tn)))
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

Node * g_slist_sort_real(Node * list)
  /*D_requires list^(x) */
  /*D_ensures  (sorted-list^(ret) & (keys^(ret) s= old(keys^(list)))) */
{
	Node * l1, * l2;

	if (list == NULL) {
		return list;
	}
	if (list->next == NULL) {
		return list;
	}
	l1 = list;
	l2 = list->next;

	Node * l2_next = l2->next;

	while(l2_next != NULL)
    /*D_invariant ((list^(list)
                    & (lseg^(list, l1)
                      * (list^(l1)
                        & (lseg^(l1, l2)
                          * (list^(l2) & ((~ (l2 l= nil)) & ((l2 |-> loc next: l2_next) * true)))))))
                & (old(keys^(list)) s= ((lseg-keys^(list, l1) union lseg-keys^(l1, l2)) union keys^(l2)))) */
	{
    l2_next = l2_next->next;
    l2 = l2_next;

		if(l2 == NULL) {
			break;
		}
		l1 = l1->next;

		l2_next = l2->next;
	}

  if (l2 != NULL) {
    l2 = l2_next;
  }

  l2 = l1->next;
  l1->next = NULL;

  if (l2 != NULL) {
    Node * t1 = g_slist_sort_real(list);
	  Node * t2 = g_slist_sort_real(l2);
  	return g_slist_sort_merge(t1, t2);
  } else {
    Node * t1 = g_slist_sort_real(list);
    return t1;
  }
}

int main(){
    Node * root = create_list(5);
    Node * res = g_slist_sort_real(root);

    return 0;
}
