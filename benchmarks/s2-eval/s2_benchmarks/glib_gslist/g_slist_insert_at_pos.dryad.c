#include "stdhipmem.h"


/*
Node * g_slist_prepend (Node * list, int data)
  /*D_requires list^(x) */
  /*D_ensures (list^(ret) & (keys^(ret) s= (old(keys^(list)) union (singleton data)))) */
/*;

Node * g_slist_append(Node * list, int data)
  /*D_requires list^(list) */
  /*D_ensures  (list^(ret) & (keys^(ret) s= (old(keys^(list)) union (singleton data)))) */
//;

Node * g_slist_insert(Node * list, int data, int pos)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  if (pos < 0) {
    return g_slist_append(list, data);
  } 
  if (pos == 0) {
    return g_slist_prepend(list, data);
  }
  Node * prev_list;
  Node * tmp_list;
  Node * new_list;

  new_list = (Node *) malloc(sizeof(Node));

  new_list->key = data;

  if (list == NULL) {
    new_list->next = NULL;
    return new_list;
  }

  tmp_list = list;
  prev_list = tmp_list;

  while(pos > 0 && tmp_list != NULL)
  /*@
   infer[@shape]
   requires true
   ensures true;
   */
  {
    pos --;
    prev_list = tmp_list;
    tmp_list = tmp_list->next;
 
  }

  Node * tmp_prev = prev_list->next;
  new_list->next = tmp_prev;
  prev_list->next = new_list;
  return list;
}
