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
} Node;

/*@ lseg<p> == self=p
   or self::node<_,n> * n::lseg<p> & self!=null; */

/*
dlseg<y> == self=y
  or self::node<_,n> * n::dlseg<y> & self!=null;
*/



Node * g_slist_prepend (Node * list, int data)
/*@
   requires list::lseg<null>
   ensures res::lseg<list>;
*/;

Node * g_slist_append(Node * list, int data)
/*@
   requires list::lseg<null>
   ensures res::lseg<list>;
*/;


void* malloc(int size) __attribute__ ((noreturn))
/*@
  case {
    size <= 0 -> requires true ensures res = null;
    size >  0 -> requires true ensures res::memLoc<h,s> & (res != null) & h;
  }
*/;


void free(Node * p) __attribute__ ((noreturn))
/*@
 requires p::memLoc<h,s> ensures p = null;
*/;



int random()
/*@
  requires true
  ensures true;
*/;


Node * g_slist_last(Node * list)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  if (list != NULL) 
  {
    while(list->next != NULL) 
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
    {
      list = list->next;
    }
   
  }
  return list;
}
