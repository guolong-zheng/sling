// ---- Definitions for GRASShopper examples  ----
#include "sls.h"
#include <stdlib.h>

/*D_defs
define pred sll^(x):
  (
  ((x l= nil) & emp) |
          ((x |-> loc next: nxt; int key: ky) * sll^(nxt))
  )
  axiom: (lseg^(x, x) * (((x l= nil) & (keys^(x) s= emptyset)) | ((~ (x l= nil)) & (~ (keys^(x) s= emptyset)))));

define pred sorted-sll^(x):
  (
  ((x l= nil) & emp) |
          ((x |-> loc next: nxt; int key: ky) *
      (sorted-sll^(nxt) & (ky le-set keys^(nxt)))
      )
  )
  axiom: (sorted-lseg^(x, x) * sll^(x));

define set-fun keys^(x):
  (case (x l= nil): emptyset;
   case ((x |-> loc next: nxt; int key: ky) * true):
    ((singleton ky) union keys^(nxt));
   default: emptyset
  ) ;

define relation lseg^(head, tail):
  (
  ((head l= tail) & emp) |
          ((head |-> loc next: nxt; int key: ky) * (lseg^(nxt, tail) & (ky le-set lseg-keys^(nxt, tail))))
  )
  axiom: ( (((head l= tail) => (emp & (lseg-keys^(head, tail) s= emptyset))) & ((tail l= nil) => (sll^(head) & (keys^(head) s= lseg-keys^(head, tail))))) &
  ( (sll^(tail) -* (sll^(head) & (keys^(head) s= (lseg-keys^(head, tail) union keys^(tail))))) &
    (((tail |-> loc next: virtual tn; int key: virtual tk) * sll^(tn)) -* ((lseg^(head, tn) & (lseg-keys^(head, tn) s= (lseg-keys^(head, tail) union (singleton tk)))) * sll^(tn))) ) ) ;

define relation sorted-lseg^(head, tail):
  (
  ((head l= tail) & emp) |
          ((head |-> loc next: nxt; int key: ky) * (sorted-lseg^(nxt, tail) & (ky le-set lseg-keys^(nxt, tail))))
  )
  axiom: ( lseg^(head, tail) &
    ( ((tail l= nil) => sorted-sll^(head)) &
  ( (sorted-sll^(tail) -* ((lseg-keys^(head, tail) le keys^(tail)) => sorted-sll^(head))) &
    (((tail |-> loc next: virtual tn; int key: virtual tk) * sll^(tn)) -* (((lseg-keys^(head, tail) set-le tk) * true) => (sorted-lseg^(head, tn) * sll^(tn)))) ) ) ) ;

define bin-set-fun lseg-keys^(head, tail):
  (case (head l= tail) : emptyset;
   case ((head |-> loc next: nxt; int key: ky) * true):
    ((singleton ky) union lseg-keys^(nxt, tail));
   default: emptyset
  ) ;
*/
// -----------------------------------------------

void insertion_sort(Node * lst)
  /*D_requires sll^(lst) */
  /*D_ensurese sorted-sll^(lst) */
{
  Node * prv = NULL;
  Node * srt = lst;
  while(srt != NULL)
    /*D_invariant ((((prv l= nil) & (srt l= lst)) & sll^(lst))
                  | ((prv |-> int key: pky) * (sll^(srt) & (pky le-set keys^(srt)))
                    * (sorted-lseg^(lst, srt) & (lseg-keys^(lst, srt) set-le pky)))) */
  {
    Node * curr = srt->next;
    Node * min = srt;
    while(curr != NULL)
      /*D_invariant (((((min |-> int key: mky) * true) & (lseg^(min, curr) & (mky le-set lseg-keys^(min, curr))))
                     * (lseg^(min, curr) & (mky le-set lseg-keys^(min, curr))))
                    * (((prv l= nil) & (srt l= lst) & sll^(lst))
                      | ((prv |-> int key: pky) * (sll^(curr) & (pky le-set keys^(curr))))))*/
    {
      if (curr->key < min->key) {
        min = curr;
      }
      curr = curr->next;
    }
    int tmp = min->key;
    int srt_key = srt->key;
    min->key = srt_key;
    prv = srt;
    srt = srt->next;
  }
}

int main(){
    Node * lst = create_list(0, 5);
    Node * res = insertion_sort(lst);
    return 0;
}
