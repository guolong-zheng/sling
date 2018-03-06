#include "dl.h"
#include <stdlib.h>

DLNode * dl_reverse(DLNode * lst)
{
  //pre
  DLNode * curr = lst;
  DLNode * rev = NULL;
  while(curr != NULL)
  {
    //loop
    DLNode * tmp;
    tmp = curr;
    curr = curr->next;
    tmp->next = rev;
    if(rev != NULL) {
      rev->prev = tmp;
    }
    rev = tmp;
  }
  //post
  return rev;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    DLNode * lst = create_list(size);
    DLNode * res = dl_reverse(lst);

    return 0;
}
