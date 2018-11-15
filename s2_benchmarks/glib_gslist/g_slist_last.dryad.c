
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} Node;

Node * g_slist_last(Node * list)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  if (list != NULL) 
  {
    while(list->next != NULL) 
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
    {
      list = list->next;
    }
   
  }
  return list;
}
