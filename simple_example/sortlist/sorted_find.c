#include "sort_list.h"

int sorted_find(SNnode * l, int k)
{
    //pre
	if (l == NULL) {
        //post
		return -1;
	} else if (l->key == k) {
        //post
		return 1;
	} else {
		int res = sorted_find(l->next, k);
        //post
		return res;
	}
}

int main( int argc, int argv[] ){
    int size;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_list(size);

    int res = sorted_find(root, (int)rand());

    return 0;
}
