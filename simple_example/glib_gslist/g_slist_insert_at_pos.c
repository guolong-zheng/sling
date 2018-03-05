#include "g_slist.h"
#include <stdlib.h>

Node * g_slist_insert(Node * list, int data, int pos)
{
  //pre
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
  {
    //loop
    pos --;
    prev_list = tmp_list;
    tmp_list = tmp_list->next;
  }

  Node * tmp_prev = prev_list->next;
  new_list->next = tmp_prev;
  prev_list->next = new_list;
  return list;
}

Node * g_slist_append(Node * list, int data)
{
  Node * new_list = (Node *) malloc(sizeof(Node));
  new_list->key = data;
  new_list->next = NULL;
  if (list != NULL) {
    Node * last = g_slist_last(list);
    last->next = new_list;
    return list;
  } else {
    return new_list;
  }
}

Node * g_slist_last(Node * list){
    if (list != NULL)
  {
    while(list->next != NULL)
    {
      list = list->next;
    }

  }
  return list;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * root = create_list(size);
    Node * res = g_slist_insert(root, rand_num(), rand()%size);

    return 0;
}
