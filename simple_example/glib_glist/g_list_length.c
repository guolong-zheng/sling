#include "g_list.h"
#include <stdlib.h>

typedef unsigned uint;

unsi g_list_length(DLNode * list, int data)
{
  //pre
  uint length;
  length = 0;
  while(list != NULL)
  {
    //loop
    length ++;
    list = list->next;
  }
  //post
  return length;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d", &size);
    DLNode * hd = create_list(size);
    uint res = g_list_length(root);

    return 0;
}
