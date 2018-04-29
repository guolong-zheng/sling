#include "header.h"
#include <stdio.h>
#include <stdlib.h>

SNnode * sll_insert_front(SNnode * x, int k)
{
        //pre
		SNnode * head = (SNnode *) malloc(sizeof(SNnode));
		head->key = k;
		head->next = x;
        //post
		return head;
}

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_sll(size);

    SNnode * res;
    res = sll_insert_front(root, (int) rand());
 	sll_insert_front(NULL, (int)rand());
    return 0;
}
