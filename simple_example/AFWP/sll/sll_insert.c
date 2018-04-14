#include "header.h"
#include <stdlib.h>
#include <stdio.h>

KNode * sll_insert(KNode * h, int v)
/*D_requires sorted-sll^(h) */
/*D_ensures  ((sorted-sll^(h) * true) & sorted-sll^(ret)) */
{
  //pre
  KNode * i = h;
  KNode * j = NULL;
  while(i != NULL && i->key <= v)
  {
    //loop
    j = i;
    i = i->next;
  }
  if (i == h) {
    KNode * hd = (KNode *)malloc(sizeof(KNode));
    hd->key = v;
    hd->next = i;
    //post
    return hd;
  }
  else {
    KNode * e = (KNode *)malloc(sizeof(KNode));
    e->key = v;
    j->next = e;
    e->next = i;
    //post
    return h;
  }
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    KNode * h = create_klist(size);
    KNode * res = sll_insert(h, rand_num());
    return 0;
}
