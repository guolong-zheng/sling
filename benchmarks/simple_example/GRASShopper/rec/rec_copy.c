#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * rec_copy_loop(Node * curr, Node * cp);
Node * rec_copy(Node * lst);

Node * rec_copy_loop(Node * curr, Node * cp)
{
  //pre
  if (curr == NULL) {
    //post
    return cp;
  } else {
    Node * old_cp = cp;
    cp = (Node *) malloc(sizeof(Node));
    cp->next = old_cp;
    Node * curr_next = curr->next;
    Node * res = rec_copy_loop(curr_next, cp);
    //post
    return res;
  }
}

Node * rec_copy(Node * lst)
{
  return rec_copy_loop(lst, NULL);
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_list(size);
    Node * res = rec_copy(lst);

    return 0;
}
