#include <vcc.h>
#include <stdlib.h>

typedef struct node {
   int key;
   struct node * next;
} Node;

Node * swap(Node * h)
{
  //pre
  if (h != NULL) {
    Node * i = h->next;
    if (i != NULL) {
      Node * j = h;
      h = h->next;
      Node * t = h->next;
      j->next = t;
      h->next = j;
    }
  }
  //post
  return h;
}
