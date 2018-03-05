#include "g_list.h"
#include <stdlib.h>

void g_list_free(DLNode * list)
{
  //pre
  DLNode * x = list;
  while(x != NULL)
  {
    //loop
    DLNode * next = x->next;
    free(x);
    x = next;
  }
  //post
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d", &size);
    DLNode * hd = create_list(size);
    g_list_free(hd);
    return 0;
}
