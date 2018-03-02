#include "circular_list.h"

CNode * circular_list_insert_front(CNode * x)
{
    //pre
	CNode * tmp = x->next;
	CNode * hd = (CNode *) malloc(sizeof(CNode)) ;
	hd->next = tmp;
	x->next = hd;
    //post
	return hd;
}

int main( int argc, char * argv[] ){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    CNode * root = create_list(size);

    CNode * res = circular_list_insert_front(root);
    return 0;
}
