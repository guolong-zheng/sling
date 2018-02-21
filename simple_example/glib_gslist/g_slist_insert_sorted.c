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
  ((x l= nil) & emp)
  | ((x |-> loc next: nxt; int key: ky)
      * (sorted-list^(nxt) & (ky lt-set keys^(nxt))))
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
  (((head l= tail) | ((head l= nil) & (tail l= nil))) & emp)
  | ((head |-> loc next: nxt; int key: ky)
      * (sorted-lseg^(nxt, tail) & (ky lt-set lseg-keys^(nxt, tail))))
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

Node * g_slist_insert_sorted(Node * list, int data)
  /*D_requires sorted-list^(list) */
  /*D_ensures (sorted-list^(ret) & (keys^(ret) s= (old(keys^(list)) union (singleton data)))) */
{
	Node * tmp_list = list;
	Node * prev_list = NULL;
	Node * new_list = NULL;

	if (list == NULL) {
		new_list = (Node *) malloc(sizeof(Node));
		new_list->key = data;
		new_list->next = NULL;
		return new_list;
	}

	while(tmp_list->next != NULL && tmp_list->key < data)
    /*D_invariant ((~ (x l= nil))) &
      ((keys^(list) s= old(keys^(list)))
        & ((sorted-list^(list) & ((sorted-lseg^(list, tmp_list)
                                & ((lseg-keys^(list, tmp_list) set-lt data)
                                & (lseg-keys^(list, tmp_list) set-lt tk))) * (sorted-list^(tmp_list)
                                & ((tmp_list |-> loc next: tmpnext; int key: tk) * sorted-list^(tmpnext)))))
            &(((prev_list l= nil) & (tmp_list l= list)) | ((((sorted-lseg^(list, prev_list) & (lseg-keys^(list, prev_list) set-lt tp)) * (prev_list |-> loc next: tmp_list; int key: tp)) & sorted-lseg^(list, tmp_list)) * true))))) */

	{
		prev_list = tmp_list;
		tmp_list = tmp_list->next;
	}

	new_list = (Node *) malloc(sizeof(Node));
	new_list->key = data;
	if (tmp_list->next == NULL && data >= tmp_list->key) {
		tmp_list->next = new_list;
		new_list->next = NULL;
		return list;
	}

	if (prev_list != NULL) {
		new_list->next = NULL;
		prev_list->next = new_list;
		new_list->next = tmp_list;
		return list;
	} else {
		new_list->next = list;
		return new_list;
	}
}

int main(){
    Node * root = create_list(5);
    Node * res = g_slist_insert_sorted(root, (int)rand());

    return 0;
}
