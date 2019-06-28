#include "header.h"
#include <stdlib.h>
#include <stdio.h>

int g_list_nth_data(DLNode * list, int n)
{
  //pre
  int res;
  while(n > 0 && list != NULL)
  {
    //loop
    n --;
    list = list->next;
  }
  if (list != NULL) {
    res = list->key;
  } else {
    res = 0;
  }
  //post
  return res;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d", &size);
    DLNode * hd = create_list(size);
    int res = g_list_nth_data(hd, rand()%size);
    g_list_nth_data(NULL, 2);
    return 0;
}
