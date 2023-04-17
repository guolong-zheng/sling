#include "header.h"
#include <stdlib.h>
#include <stdio.h>

KNode * sll_merge(KNode * i, KNode * j)
  /*D_requires (((~ (i l= nil)) & sorted-sll^(i)) * ((~ (j l= nil)) & sorted-sll^(j))) */
  /*D_ensures sorted-sll^(ret) */
{
  //pre
  KNode * h = i;
  KNode * k = NULL;
  while(i != NULL)
    /*D_invariant ((sorted-sll^(i) * sorted-sll^(j))
                  * (sorted-lseg^(h, k) * ((((k l= nil) & (h l= i)) | (k |-> loc next: i)) * sorted-sll^(i)))) */
  {
    //loop
    if (j == NULL || i->key <= j->key) {
      k = i;
      i = i->next;
    } else {
      k->next = j;
      k = j;
      j = j->next;
      k->next = i;
    }
  }
  //post
  return h;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    KNode * i = create_klist(size);
    KNode * j = create_klist(size);
    KNode * res = sll_merge(i, j);
    return 0;
}
