#include "header.h"
#include <stdio.h>
#include <stdlib.h>

SNnode * sorted_insert(SNnode *x, int k);
SNnode * insertion_sort_copy(SNnode * l);

int main( int argc, char * argv[]){
    int size;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_list(size);

    SNnode * res = insertion_sort_copy(root);
    return 0;
}

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
