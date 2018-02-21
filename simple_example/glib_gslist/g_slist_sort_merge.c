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


Node * g_slist_sort_merge(Node * l1, Node * l2)
  /*D_requires sorted-list^(l1) * sorted-list^(l2) */
  /*D_ensures (sorted-list^(ret) & (keys^(ret) s= (old(keys^(l1)) union old(keys^(l2))))) */
{
	Node * list, * l, * y;
	list = (Node *) malloc(sizeof(Node));
    y = NULL;
	list->key = INT_MIN;
	list->next = y;
	l = list;
    Node * list_next =list->next;
	while(l1 != NULL && l2 != NULL)
    /*D_invariant (((((sorted-list^(l1) * sorted-list^(l2)) * ((list |-> loc next: y) * sorted-list^(y)))
                    & ((((keys^(l1) union keys^(l2)) union keys^(y)) s= (old(keys^(l1)) union old(keys^(l2))) * true))
                    & (((y l= nil) & (l l= x)) | (((sorted-lseg^(y, l) & (lseg-keys^(y, l) set-lt kl)) * ((l |-> loc next: nill; int key: kl) & (nill l= nil))) * true))) & (((keys^(y) lt keys^(l1)) * true)
                  & ((keys^(y) lt keys^(l2)) * true))) */
	{
		if (l1->key <= l2->key)
		{
			l->next = l1;
			l1 = l1->next;
		} else {
			l->next = l2;
			l2 = l2->next;
		}
		l = l->next;
    if (y == NULL) {
      y = l;
    }

		l->next = NULL;
	}
	if (l1 != NULL) {
		l->next = l1;
	} else {
		l->next = l2;
	}
	return list_next;
}

int main(){
    Node * list1 = create_list(5);
    Node * list2 = create_list(5);
    Node * res = g_slist_sort_merge(list1, list2);

    return 0;
}
