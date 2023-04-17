#include <stdlib.h>
#include "header.h"

void splice(DLNode * h, DLNode * i)
  /*D_requires (lseg^(h, i) * ((~(i l= nil)) & dll^(i))) */
  /*D_ensures (dll^(h) * dll^(i)) */
{
  //pre
  DLNode * j;
  if (h != NULL && i != h)
  {
    j = i->prev;
    i->prev = NULL;
    j->next = NULL;
  }
  //post
}


int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    DLNode * h = create_dll(size);
    DLNode * i = h->next->next;
    splice(h, i);
    return 0;
}
