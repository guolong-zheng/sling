// ---- Common definitions for memory region examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
struct backing_file {
  int file_id;
} BackingFile;

typedef
/*D_tag mem_reg */
struct mem_reg {
  BackingFile * file;
  int file_offset;
  int file_size;
  int start_address;
  int size;
  struct mem_reg * prev;
  struct mem_reg * next;
  _(invariant file_size <= size)
} MemReg;

/*D_defs 
define pred dll^(x):
 (
   ((x l= nil) & emp) |

    ( ((x |-> loc next: y; int fileOffset: fo; int fileSize: fs; int size: sz) *
     (((y l= nil) & emp) |
     (
          ((y |-> secondary prev: x) * (~(y l= nil))) & dll^(y)
     ))
    ) & (~ (x l= nil)))
 )
 axiom: sll^(x);

define int-fun length^(x):
  (case (x l= nil): 0;
   case ((x |-> loc next: nxt) * true): 
    (1 + length^(nxt));
   default: 0
  ) ;

define pred sll^(x): 
  ( 
  ((x l= nil) & emp) | 
          ((x |-> loc next: nxt) * sll^(nxt))  
  )
  axiom: (lseg^(x, x) * (((x l= nil) & (length^(x) i= 0)) | ((~ (x l= nil)) & (0 < length^(x)))));


define relation lseg^(head, tail): 
  ( 
  ((head l= tail) & emp) | 
          ((head |-> loc next: nxt) * lseg^(nxt, tail))  
  ) 
  axiom: ( (((head l= tail) => (emp & (lseg-length^(head, tail) i= 0))) & ((tail l= nil) => (sll^(head) & (length^(head) i= lseg-length^(head, tail))))) &
  ( (sll^(tail) -* (sll^(head) & (length^(head) i= (lseg-length^(head, tail) + length^(tail))))) &
    (((tail |-> loc next: virtual tn) * sll^(tn)) -* ((lseg^(head, tn) & (lseg-length^(head, tn) i= (lseg-length^(head, tail) + 1))) * sll^(tn))) ) ) ;


define bin-int-fun lseg-length^(head, tail):
  (case (head l= tail) : 0;
   case ((head |-> loc next: nxt) * true): 
    (1 + lseg-length^(nxt, tail));
   default: 0
  ) ;
*/
// --------------------------------------------------------

_(dryad)
MemReg * memory_region_init(BackingFile * file_, 
                            int file_offset_, 
                            int file_size_, 
                            int start_address_, 
                            int size_)
  /*D_requires emp */
  /*D_ensures ((ret |-> loc file: file_; int file_offset: file_offset_; int file_size: file_size_; int start_address: start_address_; int size: size_; loc prev: nill; loc next: nill)
       & (nill l= nil)) */
{
  MemReg * mr = (MemReg *) malloc(sizeof(MemReg));
  _(assume mr != NULL)
  mr->file = file_;
  mr->file_offset = file_offset_;
  mr->file_size = file_size_;
  mr->start_address = start_address_;
  mr->size = size_;
  mr->prev = NULL;
  mr->next = NULL;
  return mr;
}

_(dryad)
MemReg * memory_region_create_user_space_region()
  /*D_requires emp */
  /*D_ensures dll^(ret) */
{
  MemReg * r  = memory_region_init(NULL, 0, 0, 0, 1);
  MemReg * r1 = memory_region_init(NULL, 0, 0, 786432, 65536);
  r->next = r1;
  r1->prev = r;
  return r;
}

_(dryad)
MemReg * split_memory_region(MemReg * curr, int offset)
  /*D_requires (dll^(curr) & ((~ (curr l= nil)) & (curr->start_address + offset < INT_MAX))) */
  /*D_ensures dll^(ret) */
{
  if (offset >= curr->size) {
    return NULL;
  }

  MemReg * old_next = curr->next;
  MemReg * next = NULL;
  if (offset > curr->file_size) {
    next = memory_region_init(NULL, 0, 0, curr->start_address + offset, curr->size - offset);
  } else {
    next = memory_region_init(curr->file, 0, 0, curr->start_address + offset, curr->size - offset);
    curr->file_size = offset;
  }

  curr->size = offset;
  next->prev = curr;
  next->next = old_next;

  if(old_next != NULL) {
    old_next->prev = next;
  }
  curr->next = next;
  return next;
}
