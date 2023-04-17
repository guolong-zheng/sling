#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * g_slist_last(Node * list)
{
    //pre
  if (list != NULL)
  {
    while(list->next != NULL)
    {
        //loop
      list = list->next;
    }

  }
  //post
  return list;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * root = create_list(size);
    Node * res = g_slist_last(root);
    g_slist_last(NULL);
    return 0;
}
