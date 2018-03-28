#include "header.h"
#include <stdlib.h>

void insertion_sort(Node * lst)
{
  //pre
  Node * prv = NULL;
  Node * srt = lst;
  while(srt != NULL)
  {
    //loop
    Node * curr = srt->next;
    Node * min = srt;
    while(curr != NULL)
    {
      //loop
      if (curr->key < min->key) {
        min = curr;
      }
      curr = curr->next;
    }
    int tmp = min->key;
    int srt_key = srt->key;
    min->key = srt_key;
    prv = srt;
    srt = srt->next;
  }
  //post
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_random(size);
    Node * res = insertion_sort(lst);
    return 0;
}
