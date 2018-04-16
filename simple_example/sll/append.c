#include "header.h"
#include <stdio.h>
#include <stdlib.h>

SNnode * sll_append(SNnode * x1, SNnode * x2)
{
  //pre
  if (x1 == NULL) {
	  //post
    return x2;
  } else {
    SNnode * tmp = sll_append(x1->next, x2);
    x1->next = tmp;
  //post
    return x1;
  }
}

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);

    int i = 0;
    SNnode * root = NULL;
    for(i = 0; i < size; i++){
        SNnode * newnode = create_node();
        root = sll_append(root, newnode);
    }

    return 0;
}
