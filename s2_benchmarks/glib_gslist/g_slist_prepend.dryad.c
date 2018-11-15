
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} Node;

Node * g_slist_prepend (Node * list, int data)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * new_list = (Node *) malloc(sizeof(Node));
  _(assume new_list != NULL)
  new_list->key = data;
  new_list->next = list;    
  return new_list;
}

