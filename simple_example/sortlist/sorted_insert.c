#include "sort_list.h"

SNnode * sorted_insert(SNnode *x, int k)
{
    //pre
	if (x == NULL) {
		SNnode * tail = (SNnode *) malloc(sizeof(SNnode));
		tail->key = k;
		tail->next = NULL;
        //post
		return tail;
	}
	else if (k > x->key) {
		SNnode * tmp = sorted_insert(x->next, k);
		x->next = tmp;
        //post
		return x;
	}
	else {
		SNnode * head = (SNnode *) malloc(sizeof(SNnode));
		head->key = k;
		head->next = x;
        //post
		return head;
	}
}

int main( int argc, int argv[] ){
    int size;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_sorted_list(size);

    SNnode * res = sorted_insert(root, rand_num());
    return 0;
}
