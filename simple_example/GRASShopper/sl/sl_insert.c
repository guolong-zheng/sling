#include "header.h"
#include <stdlib.h>

Node * sl_insert(Node * lst, Node * elt)
{
  //pre
  if (lst == NULL) {
    //post
    return elt;
  } else {
    int nondet = rand();
    Node * curr = lst;
    while(nondet && curr->next != NULL)
    {
      //loop
      nondet = rand();
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
    Node * lst = create_list(size);
    Node * elt = (Node *)malloc(sizeof(Node));
    elt->next = NULL;
    Node * res = sl_insert(lst, elt);

    return 0;
}
