
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
  struct node * last;
} Node;

void simpleq_insert_head(Node * head, Node * listelm)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * elm = (Node *) malloc(sizeof(Node));
  elm->next = NULL;
  if (head->next == NULL) {
    head->last = elm;
  }
  head->next = elm;
}
