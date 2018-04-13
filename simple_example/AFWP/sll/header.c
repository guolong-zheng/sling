#include "header.h"
#include <stlib.h>

NNode * create_list(int sz)
{
  //pre
  NNode * h = NULL;
  while(sz > 0)
  {
    //loop
    sz --;
    NNode * e = (NNode *)malloc(sizeof(NNode));
    e->next = h;
    h = e;
  }
  //post
  return h;
}

KNode * create_klist(int size){
    
}
