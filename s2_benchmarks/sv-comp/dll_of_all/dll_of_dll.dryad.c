
typedef
/*D_tag slave_item */
struct slave_item {
  struct slave_item * next;
  struct slave_item * prev;
};

_(abstract) void abort_()
    _(ensures \false) 
;


struct slave_item * alloc_or_die_slave(void)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  struct slave_item * ptr = (struct slave_item *) malloc(sizeof(struct slave_item));
  if (!ptr) {
    abort_();
  }

  ptr->next = NULL;
  ptr->prev = NULL;
  return ptr;
}

struct slave_item * dll_insert_slave(struct slave_item * x)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
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


struct slave_item * dll_create_slave(int n)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  struct slave_item * dll = NULL;
  dll = dll_insert_slave(dll);
  dll = dll_insert_slave(dll);
  while(n > 0) 
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    dll = dll_insert_slave(dll);
  }
  return dll;
}

void dll_destroy_slave(struct slave_item * dll)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

  struct slave_item * d = dll;
  while(d != NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
   {
    struct slave_item * next = d->next;
    free(d);
    d = next;
  }
}
