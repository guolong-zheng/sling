#include "header.h"
#include <stdlib.h>
#include <stdio.h>

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
    rec_dispose(NULL);
    return 0;
}
