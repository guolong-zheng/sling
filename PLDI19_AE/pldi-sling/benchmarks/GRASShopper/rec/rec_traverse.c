#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void rec_traverse(Node * lst)
{
  //pre
  if (lst != NULL) {
    Node * n = lst->next;
    rec_traverse(n);
  }
  //post
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_list(size);
    rec_traverse(lst);
    rec_traverse(NULL);
    return 0;
}
