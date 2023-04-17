#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void g_slist_free(Node * l)
{
  //pre
  Node * x = l;
  while(x != NULL)
  {
    //loop
    Node * next = x->next;
    free(x);
    x = next;
  }
  //post
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * root = create_list(size);
    g_slist_free(root);
    return 0;
}
