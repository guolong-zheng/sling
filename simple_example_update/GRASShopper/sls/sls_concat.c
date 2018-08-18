#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * sls_concat(Node * a, Node * b)
{
  //pre
  if (a == NULL) {
    //post
    return b;
  }  else {
    Node * curr;
    curr = a;
    while(curr->next != NULL)
    {
       //loop
       curr = curr->next;
    }
    curr->next = b;
    //post
    return a;
  }
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * a = create_list(1, size);
    Node * b = create_list(100, size);
    Node * res = sls_concat(a,b);
    sls_concat(NULL, create_list(1,size));
    sls_concat(create_list(2,size), NULL);
    sls_concat(NULL, NULL);
    return 0;
}
