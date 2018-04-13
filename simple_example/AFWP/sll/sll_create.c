#include "header.h"
#include <stdlib.h>

NNode * create(unsigned sz)
{
  //pre
  NNode * h = NULL;
  NNode * e = NULL;
  while(sz > 0)
  {
    //loop
    sz --;
    e = (NNode *)malloc(sizeof(NNode));
    e->next = h;
    h = e;
  }
  //post
  return h;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    NNode * res = create(size);
    return 0;
}
