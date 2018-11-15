
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
  struct node * last;
} Node;

void simpleq_init()
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * head = (Node *) malloc(sizeof(Node));
  head->next = NULL;
  head->last = head;
}

