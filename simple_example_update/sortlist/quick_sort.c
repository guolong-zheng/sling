#include "header.h"
#include <stdio.h>
#include <stdlib.h>

SNnode * concat_sorted(SNnode * l1, SNnode * l2);
SNnode * quick_sort(SNnode * l);
SNnode * find_last_sorted(SNnode * l);

int main( int argc, char * argv[] ){
    int size;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_random(size);

    SNnode * res = quick_sort(root);

    return 0;
}

SNnode * quick_sort(SNnode * l)
{
    //pre
	if (l == NULL) {
		return l;
	}
	SNnode * curr = l->next;
	int pivot = l->key;
	l->next = NULL;
	SNnode * lpt = NULL;
	SNnode * rpt = NULL;

	SNnode * tmp = curr;

	while(curr != NULL)
	{
        //loop
		tmp = curr->next;
		if (curr->key <= pivot) {
			curr->next = lpt;
			lpt = curr;
		} else {
			curr->next = rpt;
			rpt = curr;
		}
		curr = tmp;
	}

	l->next = rpt;

	SNnode * t2 = quick_sort(l);

	if (lpt == NULL) {
        //post
		return t2;
	}
	SNnode * t1 = quick_sort(lpt);
    SNnode * ret = concat_sorted(t1, t2);
    //post
	return ret;
}

SNnode * concat_sorted(SNnode * l1, SNnode * l2)
{
	if (l2 != NULL) {
		if (l1 != NULL) {
			SNnode * last = find_last_sorted(l1);
			last->next = l2;
		} else {
			l1 = l2;
		}
	}
	return l1;
}

SNnode * find_last_sorted(SNnode * l)
{
    SNnode * curr = l;
	if (curr != NULL) {
	  while (curr->next != NULL)
		{
			curr = curr->next;
		}
	}
	return curr;
}
