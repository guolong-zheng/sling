
struct node {
  struct node *next;
  int value;
};

struct llist {
  struct node *first;
  struct node *last;
};

struct iter {
    struct node *current;
};

void* malloc(int size) __attribute__ ((noreturn))
/*@
  case {
    size <= 0 -> requires true ensures res = null;
    size >  0 -> requires true ensures res::memLoc<h,s> & (res != null) & h;
  }
*/;


void free(struct node * p) __attribute__ ((noreturn))
/*@
 requires p::memLoc<_,_> ensures p = null;
*/;

void freel(struct llist * p) __attribute__ ((noreturn))
/*@
 requires p::memLoc<_,_> ensures p = null;
*/;

void freei(struct iter * p) __attribute__ ((noreturn))
/*@
 requires p::memLoc<_,_> ensures p = null;
*/;


int random()
/*@
  requires true
  ensures true;
*/;
