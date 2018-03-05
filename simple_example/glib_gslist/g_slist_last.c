#include "g_slist.h"
#include <stdlib.h>

Node * g_slist_last(Node * list)
{
    //pre
  if (list != NULL)
  {
    while(list->next != NULL)
    {
        //post
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
    return 0;
}
