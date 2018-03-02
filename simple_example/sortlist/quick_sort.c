#include "sort_list.h"

SNnode * quick_sort(SNnode * l)
{
    //pre
	if (l == NULL) {
        //post
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
		return t2;
	}
	SNnode * t1 = quick_sort(lpt);
	return concat_sorted(t1, t2);
}

int main( int argc, int argv[] ){
    int size;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_random(size);

    SNnode * res = quick_sort(root);
    //post
    return 0;
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
