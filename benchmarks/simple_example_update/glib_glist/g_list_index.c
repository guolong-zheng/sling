#include "header.h"
#include <stdlib.h>
#include <stdio.h>

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
    int res = g_list_index(hd, rand_num());
    g_list_index(NULL, rand_num());
    g_list_index(hd, 2);
    return 0;
}
