#include "stdhipmem.h"



void insertion_sort(Node * lst)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  Node * prv = NULL;
  Node * srt = lst;
  while(srt != NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    Node * curr = srt->next;
    Node * min = srt;
    while(curr != NULL) 
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
    {
      if (curr->key < min->key) {
        min = curr;
      }
      curr = curr->next;
    }
    int tmp = min->key;
    int srt_key = srt->key;
    min->key = srt_key;
    prv = srt;
    srt = srt->next;
  }
}
