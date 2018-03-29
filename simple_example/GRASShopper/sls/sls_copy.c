#include "header.h"
#include <stdlib.h>

Node * sls_copy(Node * lst)
{
  //pre
  Node * head = NULL;
  if (lst == NULL) {
    //post
    return NULL;
  }
  Node * curr = lst;
  head = (Node *) malloc(sizeof(Node));
  Node * cp = head;
  int lst_key = lst->key;
  cp->key = lst_key;
  cp->next = NULL;
  while(curr->next != NULL)
  {
    //loop
    Node * old_cp = cp;
    cp = (Node *) malloc(sizeof(Node));
    old_cp->next = cp;
    curr = curr->next;
    int curr_key = curr->key;
    cp->key = curr_key;
    cp->next = NULL;
  }
  //post
  return head;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_list(1,size);
    Node * res = sls_copy(lst);
    return 0;
}
