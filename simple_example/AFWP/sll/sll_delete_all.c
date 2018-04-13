#include "header.h"
#include <stdlib.h>

void delete_all(NNode * h)
{
  //pre
  NNode * i = h;
  NNode * j = NULL;
  while(i != NULL)
  {
    //loop
    j = i;
    i = i->next;
    j->next = NULL;
    free(j);
  }
  //post
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d", &size);
    NNode * lst = create_list(size);
    delete_all(lst);
    return 0;
}
