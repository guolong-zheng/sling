#include "g_slist.h"

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

int g_slist_position(Node * list, Node * link)
  /*D_requires ((list^(list) & (lseg^(list, link) * list^(link))) & (length^(list) < INT_MAX)) */
  /*D_ensures  (list^(old(list))
                & (((lseg^(old(list), list) & (lseg-length^(old(list), list) i= i)) * lseg^(list, link))
                  * list^(link))) */
{
	int i;

	i = 0;
	while(list != NULL)
    /*D_invariant (list^(old(list))
                  & (((lseg^(old(list), list) & ((lseg-length^(old(list), list) i= i) & ((i < INT_MAX) & (i >= 0))))
                      * lseg^(list, link))
                    * list^(link))) */
	{
		if (list == link) {
			return i;
		}
		i ++;
		list = list->next;
	}
	return -1;
}

int main(){
    Node * root = create_list(5);
    Node * list = root->next;
    int res = g_slist_position(root, list);

    return 0;
}
