
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
  struct node * prev;
} DLNode;

_(pure) int havoc();

_(dryad)
DLNode * dl_remove(DLNode * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (lst == NULL) {
    return NULL;
  } else {
    int nondet;
    DLNode * curr = lst;
    while(nondet && curr->next != NULL)
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
    {
      nondet = havoc();
      curr = curr->next;
    }
    DLNode * tmp = curr->next;
    if (tmp != NULL) {
      DLNode * tmp_next = tmp->next;
      curr->next = tmp_next;
      if(tmp_next != NULL){
        tmp_next->prev = curr;
      }
      free(tmp);
    }
    return lst;
  }
}
