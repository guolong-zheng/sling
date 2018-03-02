#include "circular_list.h"

CNode * circular_list_delete_front(CNode * x)
{
    //pre
	CNode * next = x->next;
	if (next == x) {
		free(next);
        //post
		return NULL;
	} else {
		CNode * next_next = next->next;
		free(next);
		x->next = next_next;
        //post
		return next_next;
	}
}

int main( int argc, char * argv[] ){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    CNode * root = create_list(size);

    CNode * res = circular_list_delete_front(root);

    return 0;
}
