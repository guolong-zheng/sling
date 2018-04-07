#include "header.h"
#include <stdio.h>

SNnode * find_last_sorted(SNnode * l)
{
    //pre
    SNnode * curr = l;
	if (curr != NULL) {
	  while (curr->next != NULL)
		{
            //loop
			curr = curr->next;
		}
	}
    //post
	return curr;
}

int main( int argc, char * argv[]){
    int size;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_sorted_list(0, MAX_RAND, size);

    SNnode * res= find_last_sorted(root);

    return 0;
}
