
typedef
/*D_tag slave_item */
struct list_head {
  struct list_head * next;
  struct list_head * prev;
};

void * list_del(struct list_head * entry)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
  
{
  struct list_head * prev = entry->prev;
  struct list_head * next = entry->next;
  entry->inserted = 0;
  if (prev != NULL) {
    prev->next = next;
  }
  if (next != NULL) {
    next->prev = prev;
  }
  entry->next = NULL;
  entry->prev = NULL;
  free(entry);
}
