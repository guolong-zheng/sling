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
    elt->key = -1;
    elt->next = NULL;
    Node * res = sls_insert(lst, elt);
    //sls_insert(NULL, elt);
    free(elt);
    elt = (Node *)malloc(sizeof(Node));
    elt->next = NULL;
    elt->key = 100;
    //sls_insert(lst, elt);
    free(elt);
    return 0;
}
