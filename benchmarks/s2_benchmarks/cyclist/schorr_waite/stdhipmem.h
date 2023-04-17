struct node {
  int m;
  int c;
  struct node* l;
  struct node* r;
};

void* malloc(int size) __attribute__ ((noreturn))
/*@
  case {
    size <= 0 -> requires true ensures res = null;
    size >  0 -> requires true ensures res::memLoc<h,s> & (res != null) & h;
  }
*/;


int random()
/*@
  requires true
  ensures true;
*/;
