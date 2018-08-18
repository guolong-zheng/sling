#include "header.h"
#include <stdio.h>
#include <stdlib.h>

CNode * lseg_insert_back(CNode * hd, CNode * tl)
{
    CNode * new_node = (CNode *)malloc(sizeof(CNode));
    new_node->next = hd;
    tl->next = new_node;
    return new_node;
}

CNode * circular_list_insert_back(CNode * x)
{
    //pre
	CNode * next = x->next;
	if (next == x) {
		CNode * tl = (CNode *) malloc(sizeof(CNode));
		tl->next = x;
		x->next = tl;
        //post
		return tl;
	} else {
		CNode * tl = lseg_insert_back(next, x);
		x->next = tl;
        //post
		return tl;
	}
}

int main( int argc, char * argv[] ){
    int size = 0;
    sscanf(argv[1], "%d", &size);
    CNode * root = create_list(size);
    CNode * res = circular_list_insert_back(root);
    return 0;
}
