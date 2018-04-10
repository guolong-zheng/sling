#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * sls_pairwise_sum(Node * x, Node * y)
{
  //pre
  if (x == NULL || y == NULL) {
    //post
    return NULL;
  }
  Node * curr_x = x;
  Node * curr_y = y;
  Node * z = (Node *) malloc(sizeof(Node));
  Node * last_z = z;
  int z_key = (curr_x->key + curr_y->key);
  z->key = z_key;
  z->next = NULL;
  while(curr_x->next != NULL && curr_y->next != NULL)
  {
    //loop
    Node * tmp = last_z;
    curr_x = curr_x->next;
    curr_y = curr_y->next;
    last_z = (Node *)malloc(sizeof(Node));

    last_z->next = NULL;
    z_key = (curr_x->key + curr_y->key);
    last_z->key = z_key;
    tmp->next = last_z;
  }
  //post
  return z;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * x = create_list(1, size);
    Node * y = create_list(10, size);
    Node * res = sls_pairwise_sum(x,y);
    return 0;
}
