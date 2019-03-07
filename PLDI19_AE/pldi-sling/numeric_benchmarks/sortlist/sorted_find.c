#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int sorted_find(SNnode * l, int k)
{
    //pre
	int ret;
	if (l == NULL) {
        ret = -1;
	} else if (l->key == k) {
        ret = 1;
		//return 1;
	} else {
		int res = sorted_find(l->next, k);
        ret = res;
		//return res;
	}
	//post
	return ret;
}

int main( int argc, char * argv[] ){
    int size;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_list(size);

    int res = sorted_find(root, (int)rand());

    return 0;
}
