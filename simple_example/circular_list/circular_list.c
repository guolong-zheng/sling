#include "circular_list.h"
#include <stdio.h>
#include <stdlib.h>

CNode * create_list(int size){
    CNode * hd = NULL;
    for(int i = 0; i < size; i++){
        CNode * newnode = (CNode *)malloc(sizeof(CNode));
        newnode->key = (int)rand();
        if(hd == NULL){
            hd = newnode;
            hd->next = hd;
        }else{
            newnode->next = hd->next;
            hd->next = newnode;
        }
    }

    return hd;
}

CNode * lseg_delete_back(CNode * hd, CNode * tl)
{
	CNode * next = hd->next;

	if (next == NULL) return next;
	if (next == tl) {
		free(hd);
		return next;
	} else {
		CNode * hd_next = lseg_delete_back(next, tl);
		hd->next = hd_next;
		return hd;
	}
}


CNode * circular_list_delete_back(CNode * x)
{
	CNode * next = x->next;
	if (next == x) {
		free(next);
		return NULL;
	} else {
		CNode * hd_next = lseg_delete_back(next, x);
		x->next = hd_next;
		return hd_next;
	}
}

CNode * circular_list_delete_front(CNode * x)
{
	CNode * next = x->next;
	if (next == x) {
		free(next);
		return NULL;
	} else {
		CNode * next_next = next->next;
		free(next);
		x->next = next_next;
		return next_next;
	}
}

CNode * lseg_insert_back(CNode * hd, CNode * tl){
    CNode * new_node = (CNode *)malloc(sizeof(CNode));
    new_node->next = hd;
    tl->next = new_node;

    return new_node;
}

CNode * circular_list_insert_back(CNode * x)
{
	CNode * next = x->next;

	if (next == x) {
		CNode * tl = (CNode *) malloc(sizeof(CNode));
		tl->next = x;
		x->next = tl;

		return tl;
	} else {
		CNode * tl = lseg_insert_back(next, x);
		x->next = tl;
		return tl;
	}
}

CNode * circular_list_insert_front(CNode * x)
{
	CNode * tmp = x->next;
	CNode * hd = (CNode *) malloc(sizeof(CNode)) ;
	hd->next = tmp;
	x->next = hd;
	return hd;
}
