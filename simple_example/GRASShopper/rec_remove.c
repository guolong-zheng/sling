#include "rec.h"
#include <stdlib.h>

Node * rec_remove(Node * lst)
{
  //pre
  int nondet = rand();
  if (lst == NULL) {
    //post
    return NULL;
  } else if (nondet) {
    Node * n = lst->next;
    free(lst);
    //post
    return n;
  } else {
    Node * n1 = lst->next;
    Node * n2 = rec_remove(n1);
    lst->next = n2;
    //post
    return lst;
  }
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_list(size);
    Node * res = rec_remove(lst);
    return 0;
}
