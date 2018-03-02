#include "sort_list.h"

SNnode * insertion_sort_copy(SNnode * l)
{
    //pre
	if (l == NULL) {
        //post
		return l;
	} else {
		SNnode * tl = insertion_sort_copy(l->next);
		SNnode * nl = sorted_insert(tl, l->key);
        //post
		return nl;
	}
}

int main( int argc, int argv[]){
    int size;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_list(size);

    SNnode * res = insertion_sort_copy(root);
    return 0;
}

SNnode * sorted_insert(SNnode *x, int k)
{
	if (x == NULL) {
		SNnode * tail = (SNnode *) malloc(sizeof(SNnode));
		tail->key = k;
		tail->next = NULL;
		return tail;
	}
	else if (k > x->key) {
		SNnode * tmp = sorted_insert(x->next, k);
		x->next = tmp;
		return x;
	}
	else {
		SNnode * head = (SNnode *) malloc(sizeof(SNnode));
		head->key = k;
		head->next = x;
		return head;
	}
}
