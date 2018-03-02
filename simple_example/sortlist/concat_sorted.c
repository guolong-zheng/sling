#include "sort_list.h"

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

SNnode * concat_sorted(SNnode * l1, SNnode * l2)
{
    //pre
	if (l2 != NULL) {
		if (l1 != NULL) {
			SNnode * last = find_last_sorted(l1);
			last->next = l2;
		} else {
			l1 = l2;
		}
	}
    //post
	return l1;
}

int main( int argc, int argv[]){
    int size;
    sscanf(argv[1], "%d", &size);

    SNnode * l1 = create_sorted_list(0, 50, size);
    SNnode * l2 = create_sorted_list(51, 100, size);
    SNnode * res = NULL;
    res = concat_sorted(l1, l2);

    return 0;
}
