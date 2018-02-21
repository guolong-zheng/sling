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

Node * g_slist_insert(Node * list, int data, int pos)
  /*D_requires list^(list) */
  /*D_ensures  (list^(ret) & (keys^(ret) s= (old(keys^(list)) union (singleton data)))) */
{
  if (pos < 0) {
    return g_slist_append(list, data);
  }
  if (pos == 0) {
    return g_slist_prepend(list, data);
  }
  Node * prev_list;
  Node * tmp_list;
  Node * new_list;

  new_list = (Node *) malloc(sizeof(Node));
  new_list->key = data;

  if (list == NULL) {
    new_list->next = NULL;
    return new_list;
  }

  tmp_list = list;
  prev_list = tmp_list;

  while(pos > 0 && tmp_list != NULL)
  /*D_invariant
  ( (((new_list |-> loc next: temp; int key: d) & (temp l= nil)) * ((((list^(old(list)) & (list l= old(list))) & (~ (old(list) l= nil))) & (((0 < old(pos)) & (0 <= pos)) & (old(length^(list)) i= length^(old(list))))) &
      ((((prev l= nil) & (tmp_list l= old(list))) & (lseg^(old(list), tmp_list) & ((lseg-length^(list, tmp) + pos) i= old(pos)))) * list^(tmp_list)))) |
      (((new_list |-> loc next: temp; int key: d) & (temp l= nil)) * ((((list^(old(list)) & (x l= old(list))) & (~ (old(list) l= nil))) & (((0 < old(pos)) & (0 <= pos)) & (old(length^(list)) i= length^(old(list))))) &
      (((lseg^(old(list), prev) * (prev |-> loc next: tmp_list)) & (lseg^(old(list), tmp_list) & ((lseg-length^(list, tmp_list) + pos) i= old(pos)))) * list^(tmp_list))))) */
  {
    pos --;
    prev_list = tmp_list;
    tmp_list = tmp_list->next;

  }

  Node * tmp_prev = prev_list->next;
  new_list->next = tmp_prev;
  prev_list->next = new_list;
  return list;
}

int main(){
    Node * root = create_list(5);
    Node * res = g_slist_insert(root, (int)rand(), (int)rand()%5);

    return 0;
}
