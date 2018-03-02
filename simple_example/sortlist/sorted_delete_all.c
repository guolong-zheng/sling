#include "sort_list.h"

SNnode * sorted_delete_all(SNnode * x, int k)
{
    //pre
	if (x == NULL) {
        //post
		return x;
	} else if (x->key == k) {
		SNnode * tmp = sorted_delete_all(x->next, k);
		free(x);
        //post
		return tmp;
	} else {
		SNnode * tmp = sorted_delete_all(x->next, k);
		x->next = tmp;
        //post
		return x;
	}
}

int main( int argc, int argv[] ){
    int size;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_random(size);

    SNnode * res = sorted_delete_all(root, rand_num());

    return 0;
}
