#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * g_slist_prepend (Node * list, int data)
{
  //pre
  Node * new_list = (Node *) malloc(sizeof(Node));
  new_list->key = data;
  new_list->next = list;
  //post
  return new_list;
}

int main(int argc, char * argv[]){
	int size = 0;
	sscanf(argv[1],"%d", &size);
    Node * root = create_list(size);
    Node * res = g_slist_prepend(root, rand_num());

    return 0;
}
