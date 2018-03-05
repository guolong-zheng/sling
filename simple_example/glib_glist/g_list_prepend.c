#include "g_list.h"
#include <stdlib.h>

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
    DLNode * p = root->pre;

    DLNode * res = g_list_prepend(root, rand_num(), p);

    return 0;
}
