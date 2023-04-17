#include "header.h"
#include <stdio.h>
#include <stdlib.h>
CNode * lseg_delete_back(CNode * hd, CNode * tl)
{
    //pre
	CNode * next = hd->next;
	if (next == NULL)
        //post
        return next;
	if (next == tl) {
		free(hd);
        //post
		return next;
	} else {
		CNode * hd_next = lseg_delete_back(next, tl);
		hd->next = hd_next;
        //post
		return hd;
	}
}

CNode * circular_list_delete_back(CNode * x)
{
	CNode * next = x->next;
        //pre
	if (next == x) {
		free(next);
        //post
		return NULL;
	} else {
		CNode * hd_next = lseg_delete_back(next, x);
		x->next = hd_next;
        //post
		return hd_next;
	}
}

int main( int argc, char * argv[] ){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    CNode * root = create_list(size);

    CNode * res = circular_list_delete_back(root);
    return 0;
}
