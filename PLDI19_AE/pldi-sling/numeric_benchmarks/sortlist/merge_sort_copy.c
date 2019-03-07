#include "header.h"
#include <stdio.h>
#include <stdlib.h>

SNnode * merge_sort_copy(SNnode * l1, SNnode * l2)
{
    //pre
	if (l1 == NULL) {
        //post
		return l2;
	} else if (l2 == NULL) {
        //post
		return l1;
	} else {
		if (l1->key <= l2->key) {
			SNnode * tl = merge_sort_copy(l1->next, l2);
			SNnode * nl = (SNnode *) malloc(sizeof(SNnode));
            int l1_key = l1->key;
			nl->key  = l1_key;
			nl->next = tl;
            //post
			return nl;
		} else {
			SNnode * tl = merge_sort_copy(l1, l2->next);
			SNnode * nl = (SNnode *) malloc(sizeof(SNnode));
            int l2_key = l2->key;
			nl->key = l2_key;
			nl->next = tl;
            //post
			return nl;
		}
	}
}

int main( int argc, char * argv[] ){
    int size;
    sscanf(argv[1], "%d", &size);
    SNnode * l1 = create_sorted_list(0, MAX_RAND, size);
    SNnode * l2 = create_sorted_list(0, MAX_RAND, size);

    SNnode * res = merge_sort_copy(l1, l2);

    return 0;
}
