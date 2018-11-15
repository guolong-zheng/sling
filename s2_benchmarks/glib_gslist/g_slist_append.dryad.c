
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


Node * g_slist_append(Node * list, int data)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  Node * new_list = (Node *) malloc(sizeof(Node));
  _(assume new_list != NULL)

  new_list->key = data;
  new_list->next = NULL;
  if (list != NULL) {
    Node * last = g_slist_last(list);
    last->next = new_list;
    return list;
  } else {
    return new_list;
  }

}
