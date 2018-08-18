#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * insertion_sort(Node * lst)
{
  //pre
  Node * prv = NULL;
  Node * srt = lst;
  Node * curr = NULL;
  Node * min = NULL;
  int tmp = 0;
  int srt_key = 0;
  while(srt != NULL)
  {
    //loop
    curr = srt->next;
    min = srt;
    while(curr != NULL)
    {
      //loop
      if (curr->key < min->key) {
        min = curr;
      }
      curr = curr->next;
    }
    tmp = min->key;
    srt_key = srt->key;
    min->key = srt_key;
    prv = srt;
    srt = srt->next;
  }
  //post
  return lst;
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d",&size);
    Node * lst = create_random(size);
    Node * res = insertion_sort(lst);
    insertion_sort(NULL);
    return 0;
}
