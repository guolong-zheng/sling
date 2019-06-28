#include "header.h"
#include <stdlib.h>
#include <stdio.h>

int g_list_length(DLNode * list)
{
  //pre
  int length;
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
    int res = g_list_length(hd);
    g_list_length(NULL);
    return 0;
}
