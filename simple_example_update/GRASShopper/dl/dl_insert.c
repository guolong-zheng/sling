#include "header.h"
#include <stdlib.h>
#include <stdio.h>

DLNode * dl_insert(DLNode * lst, DLNode * elt)
{
  //pre
  if (lst == NULL) {
    //post
    return elt;
  } else {
    int nondet;
    DLNode * curr = lst;
    while(nondet && curr->next != NULL)
    {
      //loop
      nondet = rand()%10 - 5;
      curr = curr->next;
    }
    DLNode * curr_next = curr->next;
    elt->next = curr_next;
    if (curr_next != NULL) {
      curr_next->prev = NULL;
    }
    curr->next = elt;
    elt->prev = curr;
    //post
    return lst;
  }
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    DLNode * lst = create_list(size);
    DLNode * elt = (DLNode *)malloc(sizeof(DLNode));
    elt->next = NULL;
    elt->prev = NULL;
    DLNode * res = dl_insert(lst, elt);
    res = dl_insert(NULL, elt);
    free(elt);
    return 0;
}
