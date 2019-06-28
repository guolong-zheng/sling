
struct node {
  struct node* next;
  int value;
};

struct stack {
  struct node* head;
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
 requires p::memLoc<h,s> ensures p = null;
*/;

void frees(struct stack * p) __attribute__ ((noreturn))
/*@
 requires p::memLoc<h,s> ensures p = null;
*/;


int random()
/*@
  requires true
  ensures true;
*/;
