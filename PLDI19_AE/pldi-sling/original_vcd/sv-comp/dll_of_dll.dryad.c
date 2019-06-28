// ---- Definitions for sv-comp examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag slave_item */
struct slave_item {
  struct slave_item * next;
  struct slave_item * prev;
};

/*D_defs 
define pred dll^(x):
 (
   (((x l= nil) & emp) |

    ((x |-> loc next: y) & (y l= nil))) |

     (
          (((x |-> loc next: nxt) * (nxt |-> secondary prev: x)) * true) &
          (  (x |-> loc next: nxt) * ((~(nxt l= nil)) & dll^(nxt)) )
    )
 )
 axiom: sll^(x);
   

define pred sll^(x): 
  ( 
  ((x l= nil) & emp) | 
          ((x |-> loc next: nxt) * sll^(nxt))  
  )
  axiom: lseg^(x, x) ;

define relation lseg^(head, tail): 
  ( 
  (((head l= tail) | ((head l= nil) & (tail l= nil))) & emp) | 
          ((head |-> loc next: nxt) * lseg^(nxt, tail))  
  ) 
axiom: ( 
      (list^(tail) -* list^(head)) &
      (((tail |-> loc next: virtual tn) * list^(tn)) -* ((lseg^(head, tn) * list^(tn)))) 
     ) ;

*/
// -------------------------------------------

_(abstract) void abort_()
    _(ensures \false) 
;

_(dryad)
struct slave_item * alloc_or_die_slave(void)
  /*D_ensures (dll^(ret) & ((ret |-> loc next: nil; loc prev: nil) * true)) */
{
  struct slave_item * ptr = (struct slave_item *) malloc(sizeof(struct slave_item));
  if (!ptr) {
    abort_();
  }

  ptr->next = NULL;
  ptr->prev = NULL;
  return ptr;
}

_(dryad)
struct slave_item * dll_insert_slave(struct slave_item * x)
  /*D_requires dll^(x) */
  /*D_ensures  ((dll^(x) * true) & dll^(ret)) */
{
  struct slave_item * item = (struct slave_item *) malloc(sizeof(struct slave_item));
  if (!item) {
    abort_();
  }
  item->next = NULL;
  item->prev = NULL;

  struct slave_item * next = x;
  item->next = next;
  if (next != NULL) {
    next->prev = item;
  }  
  return item;
}

_(dryad)
struct slave_item * dll_create_slave(int n)
  /*D_ensures dll^(ret) */
{
  struct slave_item * dll = NULL;
  dll = dll_insert_slave(dll);
  dll = dll_insert_slave(dll);
  while(n > 0) 
    /*D_invariant dll^(dll) */
  {
    dll = dll_insert_slave(dll);
  }
  return dll;
}

_(dryad)
void dll_destroy_slave(struct slave_item * dll)
  /*D_requires dll^(dll) */
  /*D_ensures  emp */
{

  struct slave_item * d = dll;
  while(d != NULL)
    /*D_invariant dll^(d) */
   {
    struct slave_item * next = d->next;
    free(d);
    d = next;
  }
}
