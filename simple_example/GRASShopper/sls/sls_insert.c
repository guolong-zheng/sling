#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * sls_insert(Node * lst, Node * elt)
{
  //pre
  if (lst == NULL || lst->key > elt->key) {
    elt->next = lst;
    //post
    return elt;
  } else {
    Node * curr = lst;
    while(curr->next != NULL && curr->next->key <= elt->key)
    {
      //loop
      curr = curr->next;
    }
    Node * curr_next = curr->next;
    elt->next = curr_next;
    curr->next = elt;
    //post
    return lst;
  }
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_list(1, size);
    Node * elt = (Node *)malloc(sizeof(Node));
    elt->key = rand();
    elt->next = NULL;
    Node * res = sls_insert(lst, elt);
    return 0;
}
