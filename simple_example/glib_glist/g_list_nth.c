#include "g_list.h"
#include <stdlib.h>

DLNode * g_list_nth(DLNode * list, int n)
 {
     //pre
  while(n > 0 && list != NULL)
  {
      //loop
    n --;
    list = list->next;
  }
  //post
  return list;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d", &size);
    DLNode * hd = create_list(size);
    DLNode * res = g_list_nth(root, rand()%size);
    return 0;
}
