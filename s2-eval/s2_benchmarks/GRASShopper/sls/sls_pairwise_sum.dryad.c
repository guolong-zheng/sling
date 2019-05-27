#include "stdhipmem.h"



Node * sls_pairwise_sum(Node * x, Node * y)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (x == NULL || y == NULL) {
    return NULL;
  } 
  Node * curr_x = x;
  Node * curr_y = y;
  Node * z = (Node *) malloc(sizeof(Node));
  Node * last_z = z;
  int z_key = (curr_x->key + curr_y->key);
  z->key = z_key;
  z->next = NULL;
  while(curr_x->next != NULL && curr_y->next != NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    Node * tmp = last_z;
    curr_x = curr_x->next;
    curr_y = curr_y->next;
    last_z = (Node *)malloc(sizeof(Node));

    last_z->next = NULL;
    z_key = (curr_x->key + curr_y->key);
    last_z->key = z_key;
    tmp->next = last_z;
  }

  return z;
}
