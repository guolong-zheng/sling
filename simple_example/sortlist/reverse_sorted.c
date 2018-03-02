#include "sort_list.h"

SNnode * reverse_sorted(SNnode * l)
{
    //pre
	SNnode * r = NULL;
	while(l != NULL)
	{
        //loop
		SNnode * t = l->next;
		l->next = r;
		r = l;
		l = t;
	}
    //post
	return r;
}

int main( int argc, int argv[] ){
    int size;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_random(size);

    SNnode * res = reverse_sorted(root);

    return 0;
}
