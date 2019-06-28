#include "header.h"
#include <stdlib.h>
#include <stdio.h>

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
  Node * old_cp = NULL;
  int curr_key = 0;
  while(curr->next != NULL)
  {
    //loop
    old_cp = cp;
    cp = (Node *) malloc(sizeof(Node));
    old_cp->next = cp;
    curr = curr->next;
    curr_key = curr->key;
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
