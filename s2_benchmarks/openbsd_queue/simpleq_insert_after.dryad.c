
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  struct node * next;
  struct node * last;
} Node;

void simpleq_insert_after(Node * head, Node * listelm)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * elm = (Node *) malloc(sizeof(Node));
  Node * lenn = listelm->next;
  elm->next = lenn;
  if (lenn == NULL) {
    head->last = elm;
  }
    listelm->next = elm;
}
