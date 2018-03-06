#include "rec.h"
#include <stdlib.h>

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
    return 0;
}
