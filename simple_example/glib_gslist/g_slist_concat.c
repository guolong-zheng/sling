#include "g_slist.h"
#include <stdlib.h>

Node * g_slist_concat(Node * list1, Node * list2)
{
  //pre
  if (list2 != NULL) {
    if (list1 != NULL) {
      Node * last = g_slist_last(list1);
      last->next = list2;
    } else {
      list1 = list2;
    }
  }
  //post
  return list1;
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
    int size;
    sscanf(argv[1],"%d",&size);
    Node * list1 = create_list(size);
    Node * list2 = create_list(size);
    Node * res = g_slist_concat(list1, list2);

    return 0;
}
