#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void delete_all(Node * h)
{
  //pre
  Node * i = h;
  Node * j = NULL;
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
    Node * lst = create_list(size);
    delete_all(lst);
    delete_all(NULL);
    return 0;
}
