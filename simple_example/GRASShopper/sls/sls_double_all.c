#include "header.h"
#include <stdlib.h>

Node * sls_double_all(Node * lst)
{
  //pre
  if (lst == NULL) {
    //post
    return NULL;
  }
  Node * curr = lst;
  Node * cp = NULL;
  Node * res = (Node *) malloc(sizeof(Node));
  cp = res;
  int curr_key = curr->key;
  cp->key = (2 * curr_key);
  cp->next = NULL;
  while(curr->next != NULL)
  {
    //loop
    Node * old_cp = cp;
    cp = (Node *) malloc(sizeof(Node));
    old_cp->next = cp;
    curr = curr->next;
    curr_key = curr->key;
    cp->key = _(unchecked)(2 * curr_key);
    cp->next = NULL;
  }
  //post
  return res;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_list(1, size);
    Node * res = sls_double_all(lst);
    return 0;
}
