#include "header.h"
#include <stdlib.h>
#include <stdio.h>

KNode * delete(KNode * h, int k);

KNode * delete(KNode * h, int k)
{
  //prev
  KNode * i = h;
  KNode * j = NULL;
  KNode * t = NULL;
  if (i == NULL) {
    //post
    return h;
  }
  while(i != NULL && t == NULL)
  {
      //loop
    if (i->key == k) {
      t = i;
    } else {
      j = i;
      i = i->next;
    }
  }

  if (i != NULL) {
    if (j == NULL){
      h = i->next;
      free(i);
    } else {
      t = i->next;
      free(i);
      j->next = t;
    }
  }
  //post
  return h;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1], "%d", &size);
    KNode * root = create_klist(size);
    KNode * res = delete(root, rand_num());
    delete(NULL, rand_num());
    delete(root, 100);
    delete(root, -100);
    delete(root, 2);
    return 0;
}
