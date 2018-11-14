#include "header.h"
#include <stdio.h>
#include <stdlib.h>

struct slave_item * create_dll(int n)
{
  struct slave_item * dll = NULL;
  int i = 0;
  for(i = 0; i < n; i++){
      Node * node = (Node *)malloc(sizeof(Node));
      node->next = NULL;
      node->prev = NULL;
      if(dll==NULL)
        dll=node;
      else{
        node->next = dll;
        dll->prev = node;
        dll=node;
      }
  }
  return dll;
}
