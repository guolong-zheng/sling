#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * concat(Node * a, Node * b)
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
       //post
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
    Node * a = create_list(size);
    Node * b = create_list(size);
    Node * res = concat(a, b);
    return 0;
}
