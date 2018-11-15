
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

typedef unsigned uint;

uint g_list_length(DLNode * list, int data) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  uint length;

  length = 0;
  while(list != NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    length ++;
    list = list->next;
  }
  return length;
}
