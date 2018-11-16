#include "stdhipmem.h"



BNode * bst_find_iter(BNode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  BNode * curr = x;
  while(curr != NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    if (curr->key == k) {
      return curr;
    } else if (k < curr->key) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  
  return curr;
}

