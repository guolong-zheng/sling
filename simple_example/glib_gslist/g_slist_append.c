#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * g_slist_last(Node * list);
Node * g_slist_append(Node * list, int data);

Node * g_slist_append(Node * list, int data)
{
  //pre
  Node * new_list = (Node *) malloc(sizeof(Node));
  new_list->key = data;
  new_list->next = NULL;
  if (list != NULL) {
    Node * last = g_slist_last(list);
    last->next = new_list;
    //post
    return list;
  } else {
    //post
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
    Node * res = g_slist_append(root, rand_num());
    return 0;
}
