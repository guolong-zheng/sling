
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

DLNode * g_list_nth(DLNode * list, int n)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  while(n > 0 && list != NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    n --;
    list = list->next;
  }
  return list;
}             

