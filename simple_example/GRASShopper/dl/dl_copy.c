#include "header.h"
#include <stdlib.h>

DLNode * dl_copy(DLNode * lst)
{
  //pre
  DLNode * curr = lst;
  DLNode * cp = NULL;
  while(curr != NULL)
  {
    //loop
    DLNode * old_cp = cp;
    cp = (DLNode *) malloc(sizeof(DLNode));
    cp->next = old_cp;
    if (old_cp != NULL) {
      old_cp->prev  = cp;
    }
    curr = curr->next;
  }
  //post
  return cp;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    DLNode * lst = create_list(size);
    DLNode * res = dl_copy(lst);

    return 0;
}
