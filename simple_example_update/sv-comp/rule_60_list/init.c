#include "header.h"
#include <stdlib.h>
#include <stdio.h>

struct list_head * list_head_init(void)
{
  //pre
  struct list_head * head = (struct list_head *) malloc(sizeof(*head));
  head->prev = NULL;
  head->next = NULL;
  //post
  return head;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1], "%d", &size);
    list_head_init();
}
