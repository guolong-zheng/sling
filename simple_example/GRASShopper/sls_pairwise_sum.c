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

Node * sls_pairwise_sum(Node * x, Node * y)
  /*D_requires (sortled-sll^(x) * sorted-sll^(y)) */
  /*D_ensures ((sortled-sll^(x) * sorted-sll^(y)) * sorted-sll^(z)) */
{
  if (x == NULL || y == NULL) {
    return NULL;
  }
  Node * curr_x = x;
  Node * curr_y = y;
  Node * z = (Node *) malloc(sizeof(Node));
  Node * last_z = z;
  int z_key = (curr_x->key + curr_y->key);
  z->key = z_key;
  z->next = NULL;
  while(curr_x->next != NULL && curr_y->next != NULL)
    /*D_invariant (((((((curr_x |-> int key: cxk) * true) & sorted-sll^(curr_x)) * (sorted-lseg^(x, curr_x) & (lseg-keys^(x, curr_x) set-le cxk)))
                    * ((((curr_y |-> int key: cyx) * true) & sorted-sll^(curr_y)) * (sorted-lseg^(y, curr_y) & (lseg-keys^(y, curr_y) set-le cyk))))
                   * (((last_z |-> loc next: nil; int key: lzk) * true) & (sorted-lseg^(z, last_z) & (lseg-keys^(z, last_z) set-le  lzk))))
                  & (lzk i= cxk + cyk)) */
  {
    Node * tmp = last_z;
    curr_x = curr_x->next;
    curr_y = curr_y->next;
    last_z = (Node *)malloc(sizeof(Node));

    last_z->next = NULL;
    z_key = _(unchecked) (curr_x->key + curr_y->key);
    last_z->key = z_key;
    tmp->next = last_z;
  }

  return z;
}

int main(){
    Node * x = create_list(1, 5);
    Node * y = create_list(10, 5);
    Node * res = sls_pairwise_sum(x,y);
    return 0;
}
