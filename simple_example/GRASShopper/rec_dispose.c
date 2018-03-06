#include "rec.h"
#include <stdlib.h>

void rec_dispose(Node * lst)
{
  //pre
  if (lst != NULL) {
    Node * n = lst->next;
    free(lst);
    rec_dispose(n);
  }
  //post
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_list(size);
    rec_dispose(lst);

    return 0;
}
