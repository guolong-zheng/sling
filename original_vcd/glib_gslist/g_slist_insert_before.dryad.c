// ---- Definitions for glib/gslist examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} Node;

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

_(dryad)
Node * g_slist_insert_before(Node * slist, Node * sibling, int data)
  /*D_requires (lseg^(x, sibling) * list^(sibling)) */
  /*D_ensures (list^(ret) & (keys^(ret) s= (old(keys^(slist)) union (singleton data)))) */
{
 
  if (slist == NULL) {
    
    slist = (Node *) malloc (sizeof (Node));
    _(assume slist != NULL)
    
    slist->key = data;

    slist->next = NULL;

    return slist;
  }
  
  Node * node = NULL;
  Node * last = NULL;
  node = slist;
 
  while(node != NULL && node != sibling) 
    /*D_invariant
      (((keys^(slist) s= old(keys^(slist))) & (~ (old(slist) l= nil))) &
      ((((last l= nil) & (slist l= node)) | (lseg^(slist, last) * (last |-> loc next: node; int key: kl))) 
          * (lseg^(node, sibling) * list^(sibling)))) */
  {
    last = node;
    node = last->next;
  }
  
  if (last == NULL) {
    node = (Node *) malloc (sizeof(Node));
    _(assume node != NULL)
    node->key = data;
    node->next = slist;
    return node;
  } else {
    node = (Node *) malloc (sizeof(Node));
    _(assume node != NULL)
    Node * tmp_last = last->next;
    node->key = data;
    node->next = tmp_last;
    last->next = node;
    return slist;
  }
}
