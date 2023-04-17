/*
 * HIP/SLEEK standard library for C program
 * 
 * Created: Oct. 31, 2013.
 */

typedef unsigned int size_t;

void* malloc(int size) __attribute__ ((noreturn))
/*@
  case {
    size <= 0 -> requires true ensures res = null;
    size >  0 -> requires true ensures res::memLoc<h,s> & (res != null) & h;
  }
*/;

void free(struct node * p) __attribute__ ((noreturn))
/*@
 requires p::memLoc<h,s> 
 ensures p = null;
*/;

void* alloca(int size) __attribute__ ((noreturn))
/*@
  case {
    size <= 0 -> requires true ensures res = null;
    size >  0 -> requires true ensures res::memLoc<h,s> & (res != null) & h;
  }
*/;

/**************************/
/*** Pointer Arithmetic ***/
/**************************/
int lt___(int* p, int* q)
/*@
  requires p::int*<vp, op> * q::int*<vq, oq>
  case {
    op <  oq -> ensures p::int*<vp, op> * q::int*<vq, oq> & res > 0;
    op >= oq -> ensures p::int*<vp, op> * q::int*<vq, oq> & res <= 0; }
*/;
