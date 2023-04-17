#include "header.h"
#include <stdlib.h>
#include <stdio.h>

DLNode * g_list_prepend(DLNode * list, int data, DLNode * p)
{
  //pre
  DLNode * ret = (DLNode *) malloc(sizeof(DLNode));
  ret->key = data;
  ret->next = list;
  ret->prev = p;
  if (list != NULL) {
    list->prev = ret;
  }
  if (p != NULL) {
     p->next = ret;
  }
  //post
  return ret;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d", &size);
    DLNode * hd = create_list(size);
    DLNode * p = hd->prev;
    DLNode * res = g_list_prepend(hd, rand_num(), p);
    p = hd->next->next;
    g_list_prepend(hd, rand_num(), p);
    g_list_prepend(NULL, rand_num(), p);
    return 0;
}
