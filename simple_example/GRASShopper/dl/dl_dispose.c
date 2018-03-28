#include "header.h"
#include <stdlib.h>

void dl_dispose(DLNode * a)
{
  //pre
  DLNode * prv = NULL;
  while(a != NULL)
  {
    //loop
    prv = a;
    a = a->next;
    free(prv);
  }
  //post
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    DLNode * lst = create_list(size);
    dl_dispose(lst);
    return 0;
}
