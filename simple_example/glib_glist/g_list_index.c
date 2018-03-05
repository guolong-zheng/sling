#include "g_list.h"
#include <stdlib.h>

int g_list_index(DLNode * list, int data)
{
  //pre
  int i;
  i = 0;
  while(list != NULL)
   {
    //loop
    if (list->key == data) {
      //post
      return i;
    }
    i ++;
    list = list->next;
   }
   //post
  return -1;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d", &size);
    DLNode * hd = create_list(size);
    int res = g_list_index(root, rand_num());

    return 0;
}
