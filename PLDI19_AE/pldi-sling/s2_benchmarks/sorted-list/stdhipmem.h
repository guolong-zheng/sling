
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
} SNnode;

void* malloc(int size) __attribute__ ((noreturn))
/*@
  case {
    size <= 0 -> requires true ensures res = null;
    size >  0 -> requires true ensures res::memLoc<h,s> & (res != null) & h;
  }
*/;


void free(SNnode * p) __attribute__ ((noreturn))
/*@
 requires p::memLoc<h,s> ensures p = null;
*/;

/*@ lseg<p> == self=p 
  or self::node<_,n> * n::lseg<p> & self!=null; */

SNnode * find_last_sorted(SNnode * l)
/*@
  requires l::lseg<null>
  ensures res::lseg<null>;
*/;

int random()
/*@
  requires true
  ensures true;
*/;
