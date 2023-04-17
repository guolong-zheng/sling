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

int g_list_length(DLNode * list)
/*@
  infer[@shape]
  requires true
  ensures true;
*/
{
  //pre
  int length;
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
  //post
  return length;
}
