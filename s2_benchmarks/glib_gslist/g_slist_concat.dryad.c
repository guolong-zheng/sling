
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} Node;

Node * g_slist_last(Node * list)
  /*D_requires list^(x) */
  /*D_ensures ((list^(old(x)) & (old(keys^(x)) s= keys^(old(x)))) & (((old(x) l= nil) => (ret l= nil)) &
                      ((~ (old(x) l= nil)) => (lseg^(old(x), ret) 
                                              * ((ret |-> loc next: temp; int key: kx) & (temp l= nil)))))) */
;

Node * g_slist_concat(Node * list1, Node * list2)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (list2 != NULL) {
    if (list1 != NULL) {
      Node * last = g_slist_last(list1);
      last->next = list2;
    } else {
      list1 = list2;
    }
  }
  return list1;
}
