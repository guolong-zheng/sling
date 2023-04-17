//#include "stdhipmem.h"


/*
 * HIP/SLEEK standard library for C program
 * 
 * Created: Oct. 31, 2013.
 */
typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

void* malloc(int size) __attribute__ ((noreturn))
/*@
  case {
    size <= 0 -> requires true ensures res = null;
    size >  0 -> requires true ensures res::memLoc<h,s> & (res != null) & h;
  }
*/;


void free(DLNode * p) __attribute__ ((noreturn))
/*@
 requires p::memLoc<h,s> ensures p = null;
*/;


int random()
/*@
  requires true
  ensures true;
*/;


DLNode * g_list_find(DLNode * list, int data) 
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  DLNode * curr = list;
  while(curr != NULL) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    if (curr->key == data) {
      break;
    }
    curr = curr->next;
  }
  return curr;
}
